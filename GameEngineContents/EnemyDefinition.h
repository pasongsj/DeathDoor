#pragma once

//SPEED

#define GRUNT_MOVE_SPEED 200.0f
#define GRUNT_JUMP_SPEED 500.0f
#define BAT_MOVE_SPEED 200.0f
//#define IDLEMOVEROT float4{0,10.0f,0}


// Default Dir
#define DEFAULT_DIR_FIREPLANT	float4{0.0f, 180.0f, 0.0f}
#define DEFAULT_DIR_BRUTE		float4{0.0f,90.0f,0.0f}
#define DEFAULT_DIR_BRUTEGOLD	float4{0.0f,90.0f,0.0f}

//SCALE
	//RENDERER
	//PHYSX COMPONENT
#define RENDERSCALE_BRUTE			30.0f
#define PHYSXSCALE_BRUTE			float4{0.0f, 150.0f, 120.0f}

#define RENDERSCALE_BRUTEGOLD		30.0f
#define PHYSXSCALE_BRUTEGOLD		float4{0.0f, 150.0f, 120.0f}

#define RENDERSCALE_FIREPLANT		120.0f
#define PHYSXSCALE_FIREPLANT		float4{0.0f, 210.0f, 120.0f}
#define FIREPLANT_ATT_RENDER_SCALE	float4{0.1f, 0.1f, 0.1f}
#define FIREPLANT_ATT_PHYSX_SCALE	float4{50.0f, 50.0f, 50.0f}

#define RENDERSCALE_GHOUL			130.0f
#define PHYSXSCALE_GHOUL			float4{0.0f, 90.0f, 60.0f}

#define RENDERSCALE_GRUNT			25.0f
#define PHYSXSCALE_GRUNT			float4{0.0f, 90.0f, 60.0f}

#define RENDERSCALE_MAGE			50.0f
#define PHYSXSCALE_MAGE				float4{0.0f, 120.0f, 80.0f}
