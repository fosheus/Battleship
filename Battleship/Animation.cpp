#include "Animation.h"


Animation::Animation(const sf::Texture * texture, sf::Vector2u imageCount, float switchCount)
{
	this->imageCount = imageCount;
	this->switchTime = switchCount;
	this->totalTime = 0.0f;
	this->currentImage.x = 0;

	uvRect.width = static_cast<int>(texture->getSize().x / static_cast<float>(imageCount.x));
	uvRect.height = static_cast<int>(texture->getSize().y / static_cast<float>(imageCount.y));

}


void Animation::update(int row, float multiplier) {
	currentImage.y = row;
	totalTime += multiplier;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

Animation::~Animation()
{
}
