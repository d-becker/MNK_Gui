#include "GameCell.hpp"

namespace ttt {

GameCell::GameCell(wl::Vec2 position,
		   int size,
		   genv::color circle_colour,
		   genv::color border_colour)
  : Button(position, size, size),
    m_circle_colour(circle_colour),
    m_border_color(border_colour),
    m_selected(false)
{
}

void GameCell::setSize(int size)
{
  Widget::setSize(size, size);
}

void GameCell::setCircleColour(genv::color colour)
{
  m_circle_colour = colour;
}

void GameCell::setBorderColour(genv::color colour)
{
  m_border_color = colour;
}

void GameCell::paint()
{
  using namespace genv;
  auto canvas_ptr = getCanvas();

  if (!canvas_ptr)
    return;

  canvas& canv = *canvas_ptr;  
  int size = getWidth(); // Width and height should be the same.

  // Background
  canv << move_to(0, 0)
       << getBackgroundColour()
       << box(size, size);

  // Border
  canv << move_to(0, 0)
       << m_border_color
       << move(size, 0)
       << move(0, size)
       << move(-size, 0)
       << move(0, -size);

  // Circle
  if (!m_selected)
    return;
  canv << m_circle_colour;
  const int radius = size / 2 - m_inset;
  const int centre = size / 2;
  for (int i = centre - radius; i <= centre + radius; ++i)
  {
    for (int j = centre - radius; j <= centre + radius; ++j)
    {
      canv << move_to(i, j) << dot;
    }
  }
  
}

void GameCell::select()
{
  m_selected = true;
}

void GameCell::deselect()
{
  m_selected = false;
}


} // namespace ttt
