#define is_down(b) input->buttons[b].is_down
#define pressed(b) input->buttons[b].is_down && input->buttons[b].changed
#define released(b) !input->buttons[b].is_down && input->buttons[b].changed

float player_xpos = 0.f;
float player_ypos = 0.f;


internal void simulate_game(Input* input, float delta_time)
{
	clear_screen(0xff5500);
	float speed = 50.f;
	if (is_down(BUTTON_UP))player_ypos += speed * delta_time;
	if (is_down(BUTTON_DOWN))player_ypos -= speed * delta_time;
	if (is_down(BUTTON_LEFT))player_xpos -= speed * delta_time;
	if (is_down(BUTTON_RIGHT))player_xpos += speed * delta_time;
	

	draw_rect(player_xpos, player_ypos, 2, 2, 0x00ff22);
}