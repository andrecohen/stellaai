#!/usr/bin/perl

my @props = ();
my %propset = ();

my %proptype = (
"Cartridge.MD5"           => 0,
"Cartridge.Manufacturer"  => 1,
"Cartridge.ModelNo"       => 2,
"Cartridge.Name"          => 3,
"Cartridge.Note"          => 4,
"Cartridge.Rarity"        => 5,
"Cartridge.Sound"         => 6,
"Cartridge.Type"          => 7,
"Console.LeftDifficulty"  => 8,
"Console.RightDifficulty" => 9,
"Console.TelevisionType"  => 10,
"Console.SwapPorts"       => 11,
"Controller.Left"         => 12,
"Controller.Right"        => 13,
"Controller.SwapPaddles"  => 14,
"Display.Format"          => 15,
"Display.YStart"          => 16,
"Display.Height"          => 17,
"Display.Phosphor"        => 18,
"Display.PPBlend"         => 19,
"Emulation.HmoveBlanks"   => 20
);

my @prop_defaults = (
  "",
  "",
  "",
  "Untitled",
  "",
  "",
  "MONO",
  "AUTO-DETECT",
  "B",
  "B",
  "COLOR",
  "NO",
  "JOYSTICK",
  "JOYSTICK",
  "NO",
  "AUTO-DETECT",
  "34",
  "210",
  "NO",
  "77",
  "YES"
);


@props = ();
while(($key, $value) = each(%proptype)) {
	$props[$value] = "";
}

print "@ARGV\n";
usage() if @ARGV != 2;

# Must provide input and output files
open(INFILE, "$ARGV[0]");
open(OUTFILE, ">$ARGV[1]");

# Parse the properties file into an array of property objects
foreach $line (<INFILE>) {
	chomp $line;

	# Start a new item
	if ($line =~ /^""/) {
		my $key = $props[$proptype{'Cartridge.MD5'}];
#		print "Inserting properties for key = $key\n";
		$propset{$key} = [ @props ];

		undef @props;
		while(($key, $value) = each(%proptype)) {
			$props[$value] = "";
		}
	} elsif ($line !~ /^$/) {
		($key, $value) = ($line =~ m/"(.*)" "(.*)"/);
		if (defined $proptype{$key}) {
			$index = $proptype{$key};
			$props[$index] = $value;
		} else {
			print "Invalid key = \'$key\' for md5 = \'$props[0]\', ignoring ...\n";
		}
	}
}

my $size = keys (%propset);
printf "Valid properties found: $size\n";

# Construct the output file in C++ format
# Walk the results array and print each item
# This array will now contain the original tree converted to a BST in array format
print OUTFILE "#ifndef DEF_PROPS_HXX\n";
print OUTFILE "#define DEF_PROPS_HXX\n";
print OUTFILE "\n";
print OUTFILE "/**\n";
print OUTFILE "  This code is generated using the 'create_props.pl' script,\n";
print OUTFILE "  located in the src/tools directory.  All properties changes\n";
print OUTFILE "  should be made in stella.pro, and then this file should be\n";
print OUTFILE "  regenerated and the application recompiled.\n";
print OUTFILE "*/\n";
print OUTFILE "\n#define DEF_PROPS_SIZE " . $size;
print OUTFILE "\n\n";
print OUTFILE "static const char* DefProps[DEF_PROPS_SIZE][" . keys( %proptype ) . "] = {\n";

my $idx = 0;
for my $key ( sort keys %propset )
{
	print OUTFILE build_prop_string(@{ $propset{$key} });

	if ($idx+1 < $size) {
		print OUTFILE ", ";
	}
	print OUTFILE "\n";
	$idx++;
}

print OUTFILE "};\n";
print OUTFILE "\n";
print OUTFILE "#endif\n";

close(INFILE);
close(OUTFILE);


sub usage {
	print "create_props.pl <INPUT STELLA PROPS> <OUTPUT C++ header>\n";
	exit(0);
}

sub build_prop_string {
	my @array = @_;
	my $result = "  { ";
	my @items = ();
	for (my $i = 0; $i < @array; $i++) {
		if($prop_defaults[$i] ne $array[$i]) {
			push(@items, "\"$array[$i]\"");
		} else {
			push(@items, "\"\"");
		}
	}

	$result .= join(", ", @items);
	$result .= " }";

	return $result;
}
