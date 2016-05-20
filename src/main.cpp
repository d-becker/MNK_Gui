#include <iostream>
#include <memory>

#include <WidgetLib/Toplevel.hpp>

#include <TicTacToe/GameFlow.hpp>
#include <TicTacToe/TraditionalGameFactory.hpp>

#include "GameCanvas.hpp"

using namespace wl;
using namespace ttt;
using namespace std;

int main()
{
  const int WIDTH = 400;
  const int HEIGHT = 400;
  
  shared_ptr<GameFactory> fact = make_shared<TraditionalGameFactory>();
  GameFlow *gf = new GameFlow({{"trad", fact}});
  gf->newGame("trad", 10, 10, 2, 5);
  
  GameCanvas *gcanv = new GameCanvas(wl::Vec2(0, 0), WIDTH, HEIGHT, gf);

  Toplevel *tl = new Toplevel(WIDTH, HEIGHT);
  tl->addChild(gcanv);
  tl->mainloop();

  delete gf;
  
  return 0;
}
