#include "WinnerLabel.hpp"

namespace ttt {

WinnerLabel::WinnerLabel(wl::Vec2 position,
			 int width,
			 int height,
			 GameFlow *game_flow)
  : wl::Label(position, width, height),
    m_game_flow(game_flow)
{
}

WinnerLabel::~WinnerLabel()
{
}

void WinnerLabel::paint()
{
  std::string text = "...";
  if (m_game_flow)
  {
    if (m_game_flow->isGamePlaying())
    {
      text = "playing...";
    } else {
      std::vector<int> winners = m_game_flow->getWinners();
      if (winners.empty())
	text = "draw";
      else
	text = winners.at(0) == 1 ? "red" : "blue";
    }
  }

  setText(text);
  Label::paint();
}

} // namespace ttt
