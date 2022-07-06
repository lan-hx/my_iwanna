//
// Created by lan on 2022/6/29.
//

#include "game/Game.h"

#include "game/_game_impl.h"

Game::Game() : game_impl_(new _game_impl) {}
Game::~Game() { delete game_impl_; }
int32_t Game::Load(const char *file_name) { return game_impl_->Load(file_name); }
void Game::Restart() { game_impl_->Restart(); }
void Game::Event(const Qt::Key &key, bool is_pressed) { game_impl_->Event(key, is_pressed); }
void Game::Step() { game_impl_->Step(); }
void Game::CloseMap() { game_impl_->CloseMap(); }
bool Game::InGame() const { return game_impl_->InGame(); }
int32_t Game::GetFrameRate() { return game_impl_->GetFrameRate(); }
std::vector<Entity *> Game::GetEntitySet() const { return game_impl_->GetEntitySet(); }
const char *Game::GetBackgroundPic() const { return game_impl_->GetBackgroundPic(); }
bool Game::IsDead() const { return game_impl_->IsDead(); }
int32_t Game::DeathCount() { return game_impl_->DeathCount(); }
double Game::PlayTime() const { return game_impl_->PlayTime(); }
const char *Game::GetDebugOutput() { return game_impl_->GetDebugOutput(); }
Entity *Game::GetPlayer() { return game_impl_->GetPlayer(); }
