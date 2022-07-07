//
// Created by lan on 2022/6/29.
//

#include "game/ViewModel.h"

#include "UI/game/gameui.h"
#include "game/Game.h"

ViewModel::ViewModel(QObject *parent, GameUI *game_ui) : QObject(parent), game_impl_(new Game), game_ui_(game_ui) {
  connect(game_ui_, &GameUI::StepSignal, game_impl_, [&]() {
    if (game_impl_->InGame()) {
      game_impl_->Step();
    }
  });
  connect(game_impl_, &Game::StepCallBack, game_ui_, &GameUI::UpdateMovies);
  connect(game_impl_, &Game::DieSignal, game_ui_, &GameUI::DieHandle);
  connect(game_impl_, &Game::UpdateInfo, game_ui_, &GameUI::UpdateInfoFromGame);
  connect(game_impl_, &Game::UpdateFrame, game_ui_, [&]() { game_ui_->update(); });
  connect(game_ui_, &GameUI::LoadSignal, game_impl_, &Game::Load);
  connect(game_ui_, &GameUI::CloseMapSignal, game_impl_, &Game::CloseMap);
  connect(game_ui_, &GameUI::KeyEventSignal, game_impl_, &Game::Event);
  connect(game_ui_, &GameUI::RestartSignal, game_impl_, &Game::Restart);
  connect(game_impl_, &Game::LoadedCallBack, game_ui_, &GameUI::AfterLoad);
}
ViewModel::~ViewModel() { delete game_impl_; }
// int32_t ViewModel::Load(const char *file_name) { return game_impl_->Load(file_name); }
// void ViewModel::Restart() { game_impl_->Restart(); }
// void ViewModel::Event(const Qt::Key &key, bool is_pressed) { game_impl_->Event(key, is_pressed); }
// void ViewModel::Step() { game_impl_->Step(); }
// void ViewModel::CloseMap() { game_impl_->CloseMap(); }
bool ViewModel::InGame() const { return game_impl_->InGame(); }
int32_t ViewModel::GetFrameRate() { return game_impl_->GetFrameRate(); }
std::vector<Entity *> ViewModel::GetEntitySet() const { return game_impl_->GetEntitySet(); }
const char *ViewModel::GetBackgroundPic() const { return game_impl_->GetBackgroundPic(); }
bool ViewModel::IsDead() const { return game_impl_->IsDead(); }
// int32_t ViewModel::DeathCount() { return game_impl_->DeathCount(); }
// double ViewModel::PlayTime() const { return game_impl_->PlayTime(); }
// const char *ViewModel::GetDebugOutput() { return game_impl_->GetDebugOutput(); }
Entity *ViewModel::GetPlayer() { return game_impl_->GetPlayer(); }
