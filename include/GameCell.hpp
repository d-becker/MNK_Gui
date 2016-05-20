#ifndef GAME_CELL_HPP
#define GAME_CELL_HPP

#include <WidgetLib/Button.hpp>

namespace ttt {

class GameCell : public wl::Button
{
public:
  GameCell(wl::Vec2 position,
	   int size,
	   genv::color circle_colour,
	   genv::color border_colour = genv::color(0, 0, 0));

  void setSize(int size);
  void setCircleColour(genv::color colour);
  void setBorderColour(genv::color colour);

  void select();
  void deselect();

  virtual void paint() override;

private:
  genv::color m_circle_colour;
  genv::color m_border_color;
  int m_inset = 2;

  bool m_selected;
};

} // namespace ttt

#endif // GAME_CELL_HPP
