#ifndef WINNER_LABEL_HPP
#define WINNER_LABEL_HPP

#include <TicTacToe/GameFlow.hpp>

#include <WidgetLib/Label.hpp>

namespace ttt {

class WinnerLabel : public wl::Label
{
public:
  WinnerLabel(wl::Vec2 position,
	      int width,
	      int height,
	      GameFlow *game_flow);

  virtual ~WinnerLabel();

  virtual void paint() override;

private:
  GameFlow *m_game_flow;
};

} // namespace ttt

#endif // WINNER_LABEL_HPP
