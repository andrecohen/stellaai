
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "AIGlueEnv.h"
#include "AIBase.h"
#include "RL_common.h"
#include "Environment_common.h"

using namespace std; 

// This is needed because aiGluePtr is non-integral type. It doesn't get 
// linked in unless declared here... 
//
// See http://cplusplus.syntaxerrors.info/index.php?title=
// Invalid_in-class_initialization_of_static_data_member_of_non-integral_type_‘const_char*’
//
AIGlue* AIGlueEnv::aiGluePtr = NULL; 
AIBase* AIGlueEnv::aiBasePtr = NULL; 

/* List of variables local to the environment */
static string msg; 
static string task_spec; 
static int screen_width; 
static int screen_height;
static AIGlue * aiGlue = NULL; 
static AIBase * aiBase = NULL; 
static Observation o; 
static Reward_observation ro; 
static int timestep; 

/* Helper functions first */
void applyAction(int action)
{
  switch(action)
  {
    case RLGACT_NOOP: 
      break; 

    case RLGACT_FIRE: 
      aiBase->pressKey(SDLK_SPACE);
      break; 

    case RLGACT_UP: 
      aiBase->pressKey(SDLK_UP);
      break; 

    case RLGACT_RIGHT: 
      aiBase->pressKey(SDLK_RIGHT);
      break; 

    case RLGACT_LEFT: 
      aiBase->pressKey(SDLK_LEFT);
      break; 
    
    case RLGACT_DOWN: 
      aiBase->pressKey(SDLK_DOWN);
      break; 

    case RLGACT_UPRIGHT: 
      aiBase->pressKey(SDLK_UP);
      aiBase->pressKey(SDLK_RIGHT);
      break; 
      
    case RLGACT_UPLEFT: 
      aiBase->pressKey(SDLK_UP);
      aiBase->pressKey(SDLK_LEFT);
      break; 
      
    case RLGACT_DOWNRIGHT: 
      aiBase->pressKey(SDLK_DOWN);
      aiBase->pressKey(SDLK_RIGHT);
      break; 
      
    case RLGACT_DOWNLEFT: 
      aiBase->pressKey(SDLK_DOWN);
      aiBase->pressKey(SDLK_LEFT);
      break; 
      
    case RLGACT_UPFIRE: 
      aiBase->pressKey(SDLK_UP);
      aiBase->pressKey(SDLK_SPACE);
      break; 

    case RLGACT_RIGHTFIRE: 
      aiBase->pressKey(SDLK_RIGHT);
      aiBase->pressKey(SDLK_SPACE); 
      break; 

    case RLGACT_LEFTFIRE: 
      aiBase->pressKey(SDLK_LEFT);
      aiBase->pressKey(SDLK_SPACE); 
      break; 
    
    case RLGACT_DOWNFIRE: 
      aiBase->pressKey(SDLK_DOWN);
      aiBase->pressKey(SDLK_SPACE); 
      break; 

    case RLGACT_UPRIGHTFIRE: 
      aiBase->pressKey(SDLK_UP);
      aiBase->pressKey(SDLK_RIGHT);
      aiBase->pressKey(SDLK_SPACE); 
      break; 
      
    case RLGACT_UPLEFTFIRE: 
      aiBase->pressKey(SDLK_UP);
      aiBase->pressKey(SDLK_LEFT);
      aiBase->pressKey(SDLK_SPACE); 
      break; 
      
    case RLGACT_DOWNRIGHTFIRE: 
      aiBase->pressKey(SDLK_DOWN);
      aiBase->pressKey(SDLK_RIGHT);
      aiBase->pressKey(SDLK_SPACE); 
      break; 
      
    case RLGACT_DOWNLEFTFIRE: 
      aiBase->pressKey(SDLK_DOWN);
      aiBase->pressKey(SDLK_LEFT);
      aiBase->pressKey(SDLK_SPACE); 
      break; 

    default: 
      aiBase->resetKeys(); 
  }
}



/* Now, RLGlue Environment function impl. */
Task_specification env_init()
{
  aiGlue = AIGlueEnv::aiGluePtr; 
  assert(aiGlue != NULL); 

  // There is a standard for this string
  // http://rlai.cs.ualberta.ca/RLBB/TaskSpecification.html
  //
  // Our observation space will vary at each timestep because we'll be 
  // sending diff_screens. So we won't be able to use the standard algorithms
  // on this thing anyway, so it's not worth encoding the task_spec string
  //
  // We can change our mind about this later if we want.
  
  o.intArray = NULL; 
  ro.o.intArray = NULL; 

  task_spec = ""; 

  return (Task_specification)task_spec.c_str(); 
}

void fullScreenObservation(Observation & obs, const Matrix & screen)
{
  //cout << "Computing full screen obs" << endl; 

  int size = 1+ 4 + screen_width*screen_height; 

  obs.numInts = size; 

  int * p = (int*)realloc(obs.intArray, size*sizeof(int)); 
  assert (p != NULL); 
  obs.intArray = p; 

  int index = 0;
  obs.intArray[index] = 0; index++; // indicate that it's a full screen obs
  obs.intArray[index] = screen_height; index++; 
  obs.intArray[index] = screen_width; index++; 

  int h = screen.size();
  int w = screen[0].size();

  obs.intArray[index] = h; index++; 
  obs.intArray[index] = w; index++;
  
	for(int y = 0; y < h; y++)
		for(int x = 0; x < w; x++)
    {
      //cout << "fullscreenobs setting y,x = " << y << "," << x;
      //cout << ", val = " << screen[y][x] << endl; 

      /*
      if (screen_width == 640 && screen[y][x] != 0) 
      {
        cout << "val != 0!" << endl;
        exit(-1); 
      }
      */

      obs.intArray[index] = screen[y][x]; 
      index++;
    }
}

void diffScreenObservation(Observation & obs)
{
  //cout << "Computing diff screen obs" << endl; 

  Matrix previous = aiBase->getPrevScreen(); 
  Matrix current = aiBase->getScreen(); 

  vector<int> pixel_diffs;

	for(size_t y=0; y < current.size(); y++){
		for(size_t x=0; x < current[y].size(); x++){
			if(current[y][x] != previous[y][x]){
				pixel_diffs.push_back(x);
				pixel_diffs.push_back(y);
				pixel_diffs.push_back(current[y][x]);
			}
		}
	}

  int size = pixel_diffs.size() + 3;

  
  obs.numInts = size; 
  int * p = (int*)realloc(obs.intArray, size*sizeof(int)); 
  assert (p != NULL); 
  obs.intArray = p; 

  obs.intArray[0] = 1; // indicate that it's a diff
  obs.intArray[1] = screen_height; 
  obs.intArray[2] = screen_width; 

  for (unsigned int i = 0; i < pixel_diffs.size(); i++) 
    obs.intArray[i+3] = pixel_diffs[i];
}

Observation env_start()
{
  aiBase = AIGlueEnv::aiBasePtr; 
  assert(aiBase != NULL);

  aiBase->resetKeys(); 
  
  screen_width = aiBase->getScreenWidth();
  screen_height = aiBase->getScreenHeight(); 
  cout << "Initial screen res, WxH = " << screen_width << " x " << screen_height << endl; 

  o.numInts = 0; 
  timestep = 0; 

  return o; 
}

Reward_observation env_step(Action a)
{
  timestep++; 
  //cout << "env_step starting, timestep " << timestep << endl; 
  bool res_change = false; 
  
  int sw = aiBase->getScreenWidth();
  int sh = aiBase->getScreenHeight(); 
  if (sh != screen_height || sw != screen_width)
  {
    cout << "Change in screen res, old WxH = " << screen_width << " x " << screen_height << endl; 
    screen_width = sw;
    screen_height = sh; 
    cout << "Change in screen res, new WxH = " << screen_width << " x " << screen_height << endl; 
    res_change = true; 
  }

  assert(a.numInts == 1);
  int action = a.intArray[0]; 

  // Apply the action
  aiBase->resetKeys(); 
  applyAction(action); 

  // Get and set the reward
  ro.r = -1; 

  // check if terminal
  ro.terminal = 0; 

  // Get observation
  if (timestep < 10)
    fullScreenObservation(ro.o, aiBase->getScreen()); 
  else
    diffScreenObservation(ro.o); 
  
  //fullScreenObservation(ro.o, aiBase->getScreen()); 

  return ro; 
}

void env_cleanup()
{
  if (o.intArray != NULL)
    free(o.intArray); 

  if (ro.o.intArray != NULL)
    free(o.intArray); 
}

void env_set_state(State_key sk)
{
}

void env_set_random_seed(Random_seed_key rsk)
{
}

State_key env_get_state()
{
  State_key sk; 
  return sk; 
}

Random_seed_key env_get_random_seed()
{
  Random_seed_key rsk; 
  return rsk; 
}

Message env_message(const Message message)
{
  msg = "This environment does not respond to messages"; 
  return (Message)msg.c_str(); 
}


