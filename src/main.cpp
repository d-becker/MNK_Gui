#include <iostream>
#include <memory>

#include <WidgetLib/evt/ButtonEvent.hpp>
#include <WidgetLib/evt/ObserverAdapter.hpp>

#include <WidgetLib/Label.hpp>
#include <WidgetLib/NumberSpinner.hpp>
#include <WidgetLib/Toplevel.hpp>

#include <TicTacToe/GameFlow.hpp>
#include <TicTacToe/TraditionalGameFactory.hpp>

#include "GameCanvas.hpp"
#include "WinnerLabel.hpp"

using namespace wl;
using namespace ttt;
using namespace std;

int main()
{
  const int WIDTH = 500;
  const int HEIGHT = 500;
  const int BAR_HEIGHT = 80;
  
  shared_ptr<GameFactory> fact = make_shared<TraditionalGameFactory>();
  GameFlow *gf = new GameFlow({{"trad", fact}});
  gf->newGame("trad", 10, 10, 2, 5);
  
  GameCanvas *gcanv = new GameCanvas(wl::Vec2(0, BAR_HEIGHT), WIDTH, HEIGHT - BAR_HEIGHT, gf);
  Label *cols_label = new Label(wl::Vec2(5, 5), 100, 25, "Columns");
  NumberSpinner<int> *cols_spinner = new NumberSpinner<int>(wl::Vec2(5, 35), 100, 25,
						    5, 50, 1, 9);

  Label *rows_label = new Label(wl::Vec2(115, 5), 100, 25, "Rows");
  NumberSpinner<int> *rows_spinner = new NumberSpinner<int>(wl::Vec2(115, 35), 100, 25,
						     5, 50, 1, 11);

  Button *b_new_game = new Button(wl::Vec2(220, 35), 50, 25);
  b_new_game->addObserver(std::make_shared< ObserverAdapter<ButtonEvent> >(
			       [=](const ButtonEvent& evt) {
			       gf->newGame("trad", cols_spinner->getCurrentValue(),
					   rows_spinner->getCurrentValue(), 2, 5);
			       return true;
			     }));

  Label *winner_label = new Label(wl::Vec2(275, 5), 100, 25, "Winner");
  WinnerLabel *wl_ = new WinnerLabel(wl::Vec2(275, 35), 100, 25, gf);
  

  Toplevel *tl = new Toplevel(WIDTH, HEIGHT);
  tl->setBackgroundColour(0, 255, 0);
  tl->addChild(gcanv);
  tl->addChild(cols_label);
  tl->addChild(cols_spinner);
  tl->addChild(rows_label);
  tl->addChild(rows_spinner);

  tl->addChild(b_new_game);
  tl->addChild(winner_label);
  tl->addChild(wl_);
  tl->mainloop();

  delete gf;
  delete tl;
  
  return 0;
}
