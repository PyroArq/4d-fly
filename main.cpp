#include <4dm.h>
#include "4DKeyBinds.h"
using namespace fdm;

// Initialize the DLLMain
initDLL

bool fly = false;

// movement rewrite
double epsilon = 0.0001;
$hook(void, Player, updatePos, World* world, double dt) {
//void Player_updatePos_H(Player* self, World* world, double dt) {
	
	if (!fly)
		return original(self, world, dt);
	
	// if we are suspiciously slightly below a full block, move us up on it a tad
	if ( floor(self->pos.y + epsilon) > floor(self->pos.y - epsilon) )
		self->pos.y += 2*epsilon;
	
	float speed = 15;
	if (self->keys.ctrl)
		speed = 100;
	if (self->inventoryManager.secondary)  // inventory open
		speed = 0;
	
	// censorship courtesy Tr1Ngle
	if (world->getType()==World::TYPE_CLIENT)
		speed /= 2;
	
	float slide = 0.1;  // natural decay time towards final speed, every this much we get e times closer
	
	// calculate forward in the horizontal plane, self-forward is down if we look down, not what we want
	glm::vec4 up = {0,1,0,0};
	glm::vec4 forward = m4::cross(self->left, up, self->over);
	
	glm::vec4 direction(0);
	
	// each movement key adds its own component, we normalize this out later
	if (self->keys.space)
		direction += up;
	if (self->keys.shift)
		direction -= up;
	if (self->keys.w)
		direction += forward;
	if (self->keys.s)
		direction -= forward;
	if (self->keys.a)
		direction += self->left;
	if (self->keys.d)
		direction -= self->left;
	if (self->keys.q)
		direction += self->over;
	if (self->keys.e)
		direction -= self->over;
	
	// normalize, but leave at 0 if no direction   the max(1,...) prevents division by 0
	direction = direction / std::max( 1.f, glm::length(direction) );
	
	glm::vec4 targetVel = direction*speed;
	
	self->deltaVel = ( targetVel - self->vel ) * float(dt)/slide;
	
	// let game do movement calculation properly, can't do much here since this handles collision
	// we could change self->vel, this was done originally, but self->deltaVel is sufficient for us
	self->crouching = false;
	self->keepOnEdge = false;
	
	return original(self, world, dt);
}

void toggleFly(){
	
	fly = !fly;
	
	// if (fly)
	// 	Player_updatePos_H(&StateGame::instanceObj->player,&*StateGame::instanceObj->world,0);
	
	printf("fly: %s\n", fly ? "on" : "off");
}


$exec {
	KeyBinds::addBind( "Toggle Flight", glfw::Keys::F, KeyBindsScope::PLAYER, [](GLFWwindow* window, int action, int mods){ if (action == GLFW_PRESS) toggleFly(); });
}
