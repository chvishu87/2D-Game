#include "gui.h"

Gui::Gui() : 
  io( IOManager::getInstance() ),
  parser( "xmlSpec/menu.xml" ),
  buttons(), 
  clicks(),
  nextIcon(0),
  click(0) 
{
  float x = parser.getXmlInt("newX");
  float y = parser.getXmlInt("newY");
  string filename = parser.getXmlStr("newFile");
  SDL_Surface* surfaceNew(io.loadAndSet(filename, true));
  Frame newFrame(surfaceNew, 
            parser.getXmlInt("newWidth"), 
            parser.getXmlInt("newHeight"), 
            parser.getXmlInt("newSrcX"), 
            parser.getXmlInt("newSrcY")); 
  buttons.push_back( Button("New", newFrame, Vector2f(x, y)) );

  x = parser.getXmlInt("openX");
  y = parser.getXmlInt("openY");
  filename = parser.getXmlStr("openFile");
  SDL_Surface* surfaceOpen(io.loadAndSet(filename, true));
  Frame openFrame(surfaceOpen, 
            parser.getXmlInt("openWidth"), 
            parser.getXmlInt("openHeight"), 
            parser.getXmlInt("openSrcX"), 
            parser.getXmlInt("openSrcY")); 
  buttons.push_back( Button("Open", openFrame, Vector2f(x, y)) );

  x = parser.getXmlInt("saveX"); 
  y = parser.getXmlInt("saveY"); 
  filename = parser.getXmlStr("saveFile");
  SDL_Surface* surfaceSave(io.loadAndSet(filename, true));
  Frame saveFrame(surfaceSave, 
            parser.getXmlInt("saveWidth"), 
            parser.getXmlInt("saveHeight"), 
            parser.getXmlInt("saveSrcX"), 
            parser.getXmlInt("saveSrcY")); 
  buttons.push_back( Button("Save", saveFrame, Vector2f(x, y)) );

  x = parser.getXmlInt("helpX"); 
  y = parser.getXmlInt("helpY"); 
  filename = parser.getXmlStr("helpFile");
  SDL_Surface* surfaceHelp(io.loadAndSet(filename, true));
  Frame helpFrame(surfaceHelp, 
            parser.getXmlInt("helpWidth"), 
            parser.getXmlInt("helpHeight"), 
            parser.getXmlInt("helpSrcX"), 
            parser.getXmlInt("helpSrcY")); 
  buttons.push_back( Button("Help", helpFrame, Vector2f(x, y)) );

  filename = parser.getXmlStr("clickoffFile");
  SDL_Surface* surfaceOff(io.loadAndSet(filename, true));
  Frame clickoff(surfaceOff, 
              parser.getXmlInt("clickoffWidth"), 
              parser.getXmlInt("clickoffHeight"), 
              parser.getXmlInt("clickoffSrcX"), 
              parser.getXmlInt("clickoffSrcX")); 
  clicks.push_back( clickoff );

  filename = parser.getXmlStr("clickonFile");
  SDL_Surface* surfaceOn(io.loadAndSet(filename, true));
  Frame clickon(surfaceOn, 
              parser.getXmlInt("clickonWidth"), 
              parser.getXmlInt("clickonHeight"), 
              parser.getXmlInt("clickonSrcX"), 
              parser.getXmlInt("clickonSrcX")); 
  clicks.push_back( clickon );
}

void Gui::draw() const {
  buttons[0].frame.draw( buttons[0].position );
  buttons[1].frame.draw( buttons[1].position );
  buttons[2].frame.draw( buttons[2].position );
  buttons[3].frame.draw( buttons[3].position );
  Vector2f pos = buttons[nextIcon].position;
  clicks[click].draw(pos[0]-70, pos[1]+20);
}

