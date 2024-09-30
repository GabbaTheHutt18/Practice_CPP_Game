#define is_down(b) input->buttons[b].is_down
#define pressed(b) input->buttons[b].is_down && input->buttons[b].changed
#define released(b) !input->buttons[b].is_down && input->buttons[b].changed

float player_pos, player_dp;
float computer_pos, computer_dp;
float arena_half_size_x = 85;
float arena_half_size_y = 45;
float player_half_size_x = 2.5;
float player_half_size_y = 12;
float ball_xpos;
float ball_ypos;
float ball_dp_x = 100;
float ball_dp_y;
float ball_half_size = 1;

int player1Score;
int player2Score;


internal bool aabb_collision(float xpos, float ypos, float half_size_x, float half_size_y, float collision_xpos, float collision_ypos, 
	float collision_half_size_x, float collision_half_size_y) {
	return(xpos + half_size_x > collision_xpos - collision_half_size_x && xpos - half_size_x < collision_xpos + collision_half_size_x && 
	ypos + half_size_y > collision_ypos - collision_half_size_y && ypos + half_size_y < collision_ypos + collision_half_size_y);

}

internal void simulate_player(float* pos, float* dp, float ddp, float delta_time)
{
	ddp -= *dp * 10.f;

	*pos = (*pos + *dp * delta_time) + ddp * delta_time * delta_time * .5f;
	*dp = *dp + ddp * delta_time;

	if (*pos + player_half_size_y > arena_half_size_y)
	{
		*pos = arena_half_size_y - player_half_size_y;
		*dp = 0;
	}
	else if (*pos - player_half_size_y < -arena_half_size_y)
	{
		*pos = player_half_size_y - arena_half_size_y;
		*dp = 0;
	}

}

internal void simulate_game(Input* input, float delta_time)
{
	clear_screen(0xff5500);
	draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0xffaa33);

	float player_ddp = 0.f;
	float computer_ddp = 0.f;
	if (is_down(BUTTON_UP))player_ddp += 2000;
	if (is_down(BUTTON_DOWN))player_ddp -= 2000;


	computer_ddp = (ball_ypos - computer_pos) * 50;
	if (computer_ddp > 1200)computer_ddp = 1200;
	if (computer_ddp < -1200)computer_ddp = -1200;
	
	
	simulate_player(&player_pos, &player_dp, player_ddp, delta_time);
	simulate_player(&computer_pos, &computer_dp, computer_ddp, delta_time);


	//ball
	{
		ball_xpos += ball_dp_x * delta_time;
		ball_ypos += ball_dp_y * delta_time;

		draw_rect(ball_xpos, ball_ypos, ball_half_size, ball_half_size, 0xffffff);
		if (aabb_collision(ball_xpos, ball_ypos, ball_half_size, ball_half_size, 80, player_pos, player_half_size_x, player_half_size_y))
		{
			ball_xpos = 80 - player_half_size_x - ball_half_size;
			ball_dp_x *= -1;
			ball_dp_y = (ball_ypos - player_pos) + (player_dp * .75f);
		}
		//need to -80 for player2
		else if (aabb_collision(ball_xpos, ball_ypos, ball_half_size, ball_half_size, -80, computer_pos, player_half_size_x, player_half_size_y)) {
			ball_xpos = -80 + player_half_size_x + ball_half_size;
			ball_dp_x *= -1;
			ball_dp_y = (ball_ypos - computer_pos) * 2 + computer_dp * .75f;
		}

		if (ball_ypos + ball_half_size > arena_half_size_y)
		{
			ball_ypos = arena_half_size_y - ball_half_size;
			ball_dp_y *= -1;

		}
		else if (ball_ypos - ball_half_size < -arena_half_size_y)
		{
			ball_ypos = -arena_half_size_y + ball_half_size;
			ball_dp_y *= -1;

		}

		if (ball_xpos + ball_half_size > arena_half_size_x)
		{
			ball_dp_x *= -1;
			ball_dp_y = 0;
			ball_xpos = 0;
			ball_ypos = 0;
			player1Score++; 

		}
		else if (ball_xpos - ball_half_size < -arena_half_size_x)
		{
			ball_dp_x *= -1;
			ball_dp_y = 0;
			ball_xpos = 0;
			ball_ypos = 0;
			player2Score++;
		}
		draw_number(player1Score, -10, 40, 1.f, 0xbbffb);
		draw_number(player2Score, 10, 40, 1.f, 0xbbffb);
	}
	draw_rect(80, player_pos, player_half_size_x, player_half_size_y, 0xff0000);
	draw_rect(-80, computer_pos, player_half_size_x, player_half_size_y, 0xff0000);

}