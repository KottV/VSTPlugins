// (c) 2019 Takamitsu Endo
//
// This file is part of WaveCymbalMod.
//
// WaveCymbalMod is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// WaveCymbalMod is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WaveCymbalMod.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "vstgui/vstgui.h"

#include "guistyle.hpp"

namespace VSTGUI {

class GroupLabel : public CControl {
public:
  GroupLabel(const CRect &size, IControlListener *listener, UTF8StringPtr text)
    : CControl(size, listener), text(text)
  {
  }

  ~GroupLabel()
  {
    if (fontID) fontID->forget();
  }

  void draw(CDrawContext *pContext) override
  {
    pContext->setDrawMode(CDrawMode(CDrawModeFlags::kAntiAliasing));
    CDrawContext::Transform t(
      *pContext, CGraphicsTransform().translate(getViewSize().getTopLeft()));

    const auto width = getWidth();
    const auto height = getHeight();

    // Background.
    pContext->setFillColor(backgroundColor);
    pContext->drawRect(CRect(0.0, 0.0, width, height), kDrawFilled);

    // Text.
    pContext->setFont(fontID);
    pContext->setFontColor(foregroundColor);
    const auto textWidth = pContext->getStringWidth(text);
    const auto textLeft = (width - textWidth) * 0.5;
    const auto textRight = (width + textWidth) * 0.5;
    pContext->drawString(text.getPlatformString(), CRect(textLeft, 0, textRight, height));

    // Border.
    pContext->setFrameColor(foregroundColor);
    pContext->setLineWidth(lineWidth);
    pContext->drawLine(
      CPoint(0.0, height * 0.5), CPoint(textLeft - margin, height * 0.5));
    pContext->drawLine(
      CPoint(textRight + margin, height * 0.5), CPoint(width, height * 0.5));

    setDirty(false);
  }

  CLASS_METHODS(GroupLabel, CControl);

  void setForegroundColor(CColor color) { foregroundColor = color; }
  void setBackgroundColor(CColor color) { backgroundColor = color; }
  void setText(UTF8String text) { this->text = text; }
  void setFont(CFontRef fontID) { this->fontID = fontID; }

protected:
  CColor foregroundColor = CColor(0, 0, 0, 255);
  CColor backgroundColor = CColor(255, 255, 255, 255);

  double fontSize = 14.0;
  UTF8String text;
  CFontRef fontID = nullptr;

  double lineWidth = 2.0;
  double margin = 10.0;
  const CLineStyle lineStyle{CLineStyle::kLineCapRound, CLineStyle::kLineJoinRound};
};

} // namespace VSTGUI
