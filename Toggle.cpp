#include "Toggle.h"
void Toggle::initStartState(bool state)
{
    this->toggled = state;

    if (toggled)
    {
        this->handleShape.setPosition(
            this->backgroundShape.getPosition().x + 0.9 * backgroundShape.getSize().x - handleShape.getSize().x,
            this->backgroundShape.getPosition().y + (this->backgroundShape.getGlobalBounds().height / 2.f) - this->handleShape.getGlobalBounds().height / 2.f
        );
        backgroundShape.setFillColor(bgHandleColor);
    }
    else
    {

        this->handleShape.setPosition(
            this->backgroundShape.getPosition().x + 0.1 * backgroundShape.getSize().x,
            this->backgroundShape.getPosition().y + (this->backgroundShape.getGlobalBounds().height / 2.f) - this->handleShape.getGlobalBounds().height / 2.f
        );

        backgroundShape.setFillColor(bgColor);
    }
}

Toggle::Toggle(Vector2f position, Vector2f size, Color bgColor, Color bgHandleColor, Color mainHandleColor, bool state)
{
    this->bgColor = bgColor;
    this->bgHandleColor = bgHandleColor;
    this->mainHandleColor = mainHandleColor;

    this->backgroundShape.setPosition(position);
    this->backgroundShape.setFillColor(bgColor);
    this->backgroundShape.setSize(size);

    this->handleShape.setSize(Vector2f(0.9f * size.y , 0.9f * size.y));
    this->handleShape.setFillColor(mainHandleColor);

    initStartState(state);

}

Toggle::~Toggle()
{

}

const bool Toggle::isToggled()
{
    return toggled;
}

void Toggle::toggle()
{
    toggled = !toggled;

    if (toggled)
    {
        this->handleShape.setPosition(
            this->backgroundShape.getPosition().x + 0.9 * backgroundShape.getSize().x - handleShape.getSize().x,
            this->backgroundShape.getPosition().y + (this->backgroundShape.getGlobalBounds().height / 2.f) - this->handleShape.getGlobalBounds().height / 2.f
        );
        backgroundShape.setFillColor(bgHandleColor);
    }
    else
    {

        this->handleShape.setPosition(
            this->backgroundShape.getPosition().x + 0.1 * backgroundShape.getSize().x,
            this->backgroundShape.getPosition().y + (this->backgroundShape.getGlobalBounds().height / 2.f) - this->handleShape.getGlobalBounds().height / 2.f
        );

        backgroundShape.setFillColor(bgColor);
    }
}

void Toggle::update(const Vector2f& mousePosition, Event event)
{
    if (this->backgroundShape.getGlobalBounds().contains(mousePosition))
    {
        if (event.type == event.MouseButtonPressed && holdUp)
        {
            toggle();
            holdUp = false;
        }
        if (event.type == event.MouseButtonReleased)
        {
            holdUp = true;
        }
    }
}

void Toggle::render(RenderTarget* target)
{
    target->draw(backgroundShape);
    target->draw(handleShape);
}
