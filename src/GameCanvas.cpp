#include "GameCanvas.hpp"

#include <cmath>

#include <WidgetLib/evt/MouseEvent.hpp>
#include <WidgetLib/evt/ObserverAdapter.hpp>
#include <WidgetLib/Util.hpp> // For vect_contains

namespace ttt {

GameCanvas::GameCanvas(wl::Vec2 position,
		       int width,
		       int height,
		       GameFlow *game_flow)
  : Widget(position, width, height),
    m_game_flow(game_flow)
{
  setBackgroundColour(255, 255, 255);

  // Super observers
  addMouseSuperObserver(std::make_shared< wl::ObserverAdapter<wl::MouseEvent> >([this](const wl::MouseEvent& evt) {
	if (evt.getEvtType() == wl::MouseEvent::CLICKED_ON_WIDGET
	    && evt.getMouseButton() == wl::MouseEvent::MOUSE_BTN::LEFT)
	{
	  ttt::Vec2 cell_coords = get_cell_by_mouse_pos(evt.getMousePos());
	  if (m_game_flow)
	    m_game_flow->takeMove(cell_coords);
	  return true;
	}

	return false;
      }));
}

GameCanvas::~GameCanvas()
{
}

void GameCanvas::paint()
{
  using namespace genv;
  if (auto canv_ptr = getCanvas())
  {
    const int width = getWidth();
    const int height = getHeight();
    const genv::color background = getBackgroundColour();
    
    // Painting the background
    canvas& canv = *canv_ptr;
    canv << move_to(0, 0)
	 << background
	 << box(width, height);

    // Painting the table
    if (std::shared_ptr<const Board> board = get_board())
    {
      calculate_size_info(board);
      int cols = board->getWidth();
      int rows = board->getHeight();
      for (int i = 0; i < cols; ++i)
      {
	for (int j = 0; j < rows; ++j)
	{
	  canv << move_to(m_offset_x + i * m_cellsize,
			  m_offset_y + j * m_cellsize);

	  bool winning_cell = is_cell_winning(i, j);
	  const genv::color bg = winning_cell ? m_win_background : background;
	  
	  int player = board->get(i, j);
	  genv::color circle(0, 0, 0);
	  bool draw_circle = true;
	  switch (player)
	  {
	  case 0 : {draw_circle = false; break;}
	  case 1 : {circle = genv::color(255, 0, 0); break;}
	  case 2 : {circle = genv::color(0, 0, 255); break;}
	  default: break;
	  }
	  
	  paint_cell(canv, bg, draw_circle, circle);
	}
      }
    }
  }
}

// Private
std::shared_ptr<const Board> GameCanvas::get_board()
{
  if (m_game_flow)
  {
    std::shared_ptr<const Game> game = m_game_flow->getGame();
    if (game)
    {
      std::shared_ptr<const Board> board = game->getBoard();
      return board;
    }
  }

  return nullptr;
}

void GameCanvas::calculate_size_info(std::shared_ptr<const Board> board)
{
  int width = getWidth();
  int height = getHeight();
  
  int cols = board->getWidth();
  int rows = board->getHeight();
      
  int cell_width = width / cols;
  int cell_height = height / rows;
  m_cellsize =  std::min(cell_width, cell_height);

  m_offset_x = (width - m_cellsize * cols) / 2;
  m_offset_y = (height - m_cellsize * rows) / 2;
}

void GameCanvas::paint_cell(genv::canvas& canv,
			    genv::color bg,
			    bool draw_circle,
			    genv::color circle_colour,
			    genv::color border)
{
  using namespace genv;
  // Background
  canv << bg
       << box(m_cellsize, m_cellsize);

  // Border
  canv << border
       << line(-m_cellsize, 0)
       << line(0, -m_cellsize)
       << line(m_cellsize, 0)
       << line(0, m_cellsize);
  
  // Circle
  if (!draw_circle) // No need to draw a circle with
		    // the same colour as the background
    return;
  
  canv << move(-m_cellsize / 2, -m_cellsize / 2);
  canv << circle_colour;
  const int radius = m_cellsize * 0.4;
  for (int i = -radius; i <= radius; ++i)
  {
    for (int j = -radius; j <= radius; ++j)
    {
      if (i*i + j*j <= radius*radius)
      {
	canv << move(i, j)
	     << dot
	     << move(-i, -j);
      }
    }
  }
}

ttt::Vec2 GameCanvas::get_cell_by_mouse_pos(const wl::Vec2& pos) const
{
  int x_coord = (pos.x - m_offset_x) / m_cellsize;
  int y_coord = (pos.y - m_offset_y) / m_cellsize;

  return Vec2(x_coord, y_coord);
}

bool GameCanvas::is_cell_winning(int x, int y) const
{
  if (!m_game_flow)
    return false;

  Vec2 pos(x, y);
  const std::vector< std::vector<Vec2> >& winners_pos
                                          = m_game_flow->getWinnersPositions();
  for (const std::vector<Vec2>& vec : winners_pos)
  {
    if (wl::vec_contains(vec, pos))
	return true;
  }
  
  return false;  
}

} // namespace ttt
