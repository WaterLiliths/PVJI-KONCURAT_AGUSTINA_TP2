#include "Game.h"

Game::Game() {
	game_won = false;
	game_over = false;
}
Game::~Game() {

}
void Game::init() {
	assets.load();

	platforms.emplace_back(Vector2{ 0, 648 }, 23, GROUND);
	platforms.emplace_back(Vector2{ 0, 612 }, 23, FLOOR);
	platforms.emplace_back(Vector2{ 36, 576 }, 1, TREE_STUMP);
	platforms.emplace_back(Vector2{ 756, 576 }, 1, TREE_STUMP);
	platforms.emplace_back(Vector2{ 36, 540 }, 13, TREE);
	platforms.emplace_back(Vector2{ 756, 540 }, 13, TREE);
	platforms.emplace_back(Vector2{ 72, 540 }, 19, BRANCH);
	platforms.emplace_back(Vector2{ 72, 468 }, 19, BRANCH);
	platforms.emplace_back(Vector2{ 72, 396 }, 19, BRANCH);
	platforms.emplace_back(Vector2{ 72, 324 }, 19, BRANCH);
	platforms.emplace_back(Vector2{ 72, 252 }, 19, BRANCH);
	platforms.emplace_back(Vector2{ 72, 180 }, 19, BRANCH);
	platforms.emplace_back(Vector2{ 18, 90 }, 22, TREE_BUSH);

	stacks.emplace_back(208, 78, 720, true);
	stacks.emplace_back(352, 78, 720, false);
	stacks.emplace_back(496, 78, 720, true);

	queues.emplace_back(136, 78, 720, false);
	queues.emplace_back(280, 78, 720, true);
	queues.emplace_back(424, 78, 720, false);

	for (auto& platform : platforms) {
		platform.assign_platform_hitbox();
	}

	for (auto& stack : stacks) {
		stack.init_enemies();
	}

	for (auto& queue : queues) {
		queue.init_enemies();
	}
}
void Game::update() {

	if (game_won || game_over) {
		if (IsKeyPressed(KEY_R)) {
			restart_game();
			return;
		}
		return; //Corte ante la condición de victoria o derrota.
	}
	
	float delta_time = GetFrameTime();
	timer.advance(delta_time);

	//Condición de derrota si llega el tiempo a cero.
	if (timer.get_time_over()) {
		game_over = true;
	}

	player.update(assets);

	for (auto& stack : stacks) {
		stack.loop();
	};

	for (auto& queue : queues) {
		queue.loop();
	}

	check_collisions();

}
void Game::draw() {

	DrawTexture(assets.background, 0, -70, WHITE);

	if(!game_won && !game_over) { //Solo dibujo el juego si todavía se está jugando
		timer.draw(utilities);

		for (auto& platform : platforms) {
			platform.draw(assets);
		}

		door.draw(assets);

		for (auto& stack : stacks) {
			stack.draw(assets);
		}

		for (auto& queue : queues) {
			queue.draw(assets);
		}

		player.draw(assets);
	}
	
	if (game_won) {
		utilities.draw_centerd_text("Has ganado!", GetScreenWidth(), 250, 50, GREEN);
		utilities.draw_centerd_text("Presiona 'R' para volver a jugar", GetScreenWidth(), 305, 25, GRAY);
	}

	if (game_over) {
		utilities.draw_centerd_text("Has perdido!", GetScreenWidth(), 250, 50, RED);
		utilities.draw_centerd_text("Presiona 'R' para volver a jugar", GetScreenWidth(), 305, 20, GRAY);
	}
}
void Game::check_collisions() {
	check_platform_collisions();
	check_enemies_collisions();
	check_door_collision();
}
void Game::check_platform_collisions() {
	Rectangle player_hb = player.get_hitbox();
	bool is_collisioning = false;


	for (auto& platform : platforms) {
		Rectangle plat_hb = platform.get_hitbox();

		//Chequea las plataformas que pueden subirse "desde abajo".
		if (platform.get_platform_type() == BRANCH || platform.get_platform_type() == TREE_BUSH) {

			if (CheckCollisionRecs(player_hb, plat_hb) && player.get_velocity().y > 0) { //Si el juagdor cae desde arriba
				if (player.get_velocity().y > 0) {
					player.set_velocity_y(0);
					player.set_position({ player.get_position().x, plat_hb.y - player_hb.height });
				}
				player.set_is_on_floor(true);
				is_collisioning = true;
			}		
		
		}

		else if (platform.get_platform_type() == TREE || platform.get_platform_type() == TREE_STUMP) {
			if (CheckCollisionRecs(player_hb, plat_hb)) {
				Vector2 prev_pos = player.get_previous_position();

				float prev_right = prev_pos.x + player_hb.width; //A la derecha de la colisión (va hacia la izquierda)
				float prev_left = prev_pos.x; //A la izquierda de la colisión (va hacia la derecha)

				// Yendo hacia la izquierda
				if (prev_right <= plat_hb.x) {
					player.set_position({ plat_hb.x - player_hb.width,	player.get_position().y });
				}

				// Yendo hacia la derecha
				else if (prev_left >= plat_hb.x + plat_hb.width) {
					player.set_position({ plat_hb.x + plat_hb.width, player.get_position().y });
				}
			}
		}
		else
		{
			if (CheckCollisionRecs(player_hb, plat_hb) && player.get_velocity().y >= 0) {
				player.set_velocity_y(0);
				player.set_position({ player.get_position().x, plat_hb.y - player_hb.height });
				player.set_is_on_floor(true);
				is_collisioning = true;
			}
		}
	}
	if (!is_collisioning)
		player.set_is_on_floor(false);
}
void Game::check_enemies_collisions() {
	for (auto& queue : queues) {
		if (queue.check_collisions(player)) {
			TraceLog(LOG_INFO, "COLISIÓN");
			player.restart();
		}
	}

	for (auto& stack : stacks) {
		if (stack.check_collisions(player)) {
			player.restart();
		}
	}
}
void Game::check_door_collision() {
	if (CheckCollisionRecs(player.get_hitbox(), door.get_hitbox())) {
		game_won = true;

	}
}
void Game::win_game() {
	TraceLog(LOG_INFO, "Has ganado");
}
void Game::lose_game() {

}
void Game::restart_game() {
	game_over = false;
	game_won = false;
	timer.restart();
	player.restart();

}
void Game::unload() {
	assets.unload();
}