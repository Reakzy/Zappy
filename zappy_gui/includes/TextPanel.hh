/*
** TextPanel.hh for zappy_gui in /home/werp/rendu/zappy_gui/TextPanel.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Sun Jul 02 09:21:14 2017 Paul Wéry
** Last update Sun Jul 02 09:21:14 2017 Paul Wéry
*/

#ifndef ZAPPY_GUI_TEXTPANEL_HH
#define ZAPPY_GUI_TEXTPANEL_HH

# include <memory>
# include <vector>
# include "irrlicht.h"

class TextPanel
{

  irr::gui::IGUIEnvironment			*guiEnvironment;
  irr::gui::IGUIFont				*guiFont;
  irr::core::position2d<irr::u32>		position;
  irr::core::dimension2d<irr::u32>		dimension;
  std::shared_ptr<irr::core::rect<irr::u32>>	surface;
  std::vector<irr::core::stringw>		fonts;
  std::vector<irr::video::SColor>		colorsFont;
  bool						visible;

 public:

  bool			isVisible() const;
  void			setVisible(bool state);
  void			addPrintableText(const std::string &text, irr::video::SColor color);
  void			drawPanel();
  void			createPanel(irr::gui::IGUIEnvironment *guiEnvironment,
					  const irr::core::position2d<irr::u32> &position,
					  const irr::core::dimension2d<irr::u32> &dimension);

  TextPanel();
  TextPanel(const TextPanel &) = delete;
  ~TextPanel();
  TextPanel		&operator=(const TextPanel &) = delete;
};


#endif //ZAPPY_GUI_TEXTPANEL_HH
