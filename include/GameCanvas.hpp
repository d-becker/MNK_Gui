#ifndef GAME_CANVAS_HPP
#define GAME_CANVAS_HPP

#include <TicTacToe/GameFlow.hpp>
#include <WidgetLib/Widget.hpp>

namespace ttt {

class GameCanvas : public wl::Widget
{
public:
  GameCanvas(wl::Vec2 position,
	     int width,
	     int height,
	     GameFlow *game_flow);

  virtual ~GameCanvas();

  virtual void paint() override;
  
private:
  // Returns the board that belongs to m_game's \c Game object. If either of
  // the objects in the chain is nullptr, returns nullptr.
  std::shared_ptr<const Board> get_board();

  void calculate_size_info(std::shared_ptr<const Board> board);
  void paint_cell(genv::canvas& canv,
		  genv::color bg,
		  genv::color circle,
		  genv::color border = genv::color(0, 0, 0));
  ttt::Vec2 get_cell_by_mouse_pos(const wl::Vec2& pos) const;
  
  GameFlow *m_game_flow;
  int m_cellsize;
  int m_offset_x;
  int m_offset_y;

  const genv::color m_win_background = genv::color(255,255,0);
};

} // namespace ttt

#endif // GAME_CANVAS_HPP
