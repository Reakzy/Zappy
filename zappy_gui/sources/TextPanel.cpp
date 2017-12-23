/*
** TextPanel.cpp for zappy_gui in /home/werp/rendu/zappy_gui/TextPanel.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Sun Jul 02 09:21:14 2017 Paul Wéry
** Last update Sun Jul 02 09:21:14 2017 Paul Wéry
*/

#include "TextPanel.hh"

TextPanel::TextPanel()
{
  this->visible = true;
}

TextPanel::~TextPanel()
{

}

void TextPanel::createPanel(irr::gui::IGUIEnvironment *guiEnvironment,
			    const irr::core::position2d<irr::u32> &position,
			    const irr::core::dimension2d<irr::u32> &dimension)
{
  this->guiEnvironment = guiEnvironment;
  if (this->guiEnvironment != nullptr)
    this->guiFont = this->guiEnvironment->getFont("./assets/fonts/font.bmp");
  this->surface.reset(new irr::core::rect<irr::u32>(position, dimension));
  this->position = position;
  this->dimension = dimension;
  if (this->guiFont != nullptr)
    this->guiFont->setKerningHeight(this->guiFont->getDimension(L"A").Height);
}

void TextPanel::drawPanel()
{
  irr::s32				space;
  irr::core::rect<irr::s32>		posText;

  if (this->guiFont == nullptr || !this->visible)
    return ;
  space = this->guiFont->getKerningHeight() + this->guiFont->getKerningHeight() / 4;
  while (this->fonts.size() > 0 && (space + 1) * this->fonts.size() > this->dimension.Height)
    this->fonts.erase(this->fonts.begin());
  for (unsigned int index = 0; index < this->fonts.size(); index++)
    {
      posText.UpperLeftCorner.X = this->position.X;
      posText.UpperLeftCorner.Y = this->position.Y + space * index;
      this->guiFont->draw(this->fonts.at(index), posText, colorsFont.at(index));
    }
}

void TextPanel::addPrintableText(const std::string &text, irr::video::SColor color)
{
  this->fonts.push_back(text.c_str());
  this->colorsFont.push_back(color);
}

void TextPanel::setVisible(bool state)
{
  this->visible = state;
}

bool TextPanel::isVisible() const
{
  return (this->visible);
}
