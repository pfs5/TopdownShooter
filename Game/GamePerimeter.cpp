#include "GamePerimeter.h"
#include "Display.h"

GamePerimeter::GamePerimeter() {
	// Init shapes
	sf::Color fillColor{ 255, 0, 0, 100 };
	sf::Color edgeColor{ 200, 0, 0};

	float winWidth = static_cast<float>(Display::WIDTH);
	float winHeight = static_cast<float>(Display::HEIGHT);

	m_shapeTop.setFillColor(fillColor);
	m_shapeTop.setSize(sf::Vector2f{ winWidth, 0.f });
	m_shapeTop.setOrigin(sf::Vector2f{0.f, 0.f});
	m_shapeTop.setPosition(sf::Vector2f{0.f, 0.f});

	m_shapeBottom.setFillColor(fillColor);
	m_shapeBottom.setSize(sf::Vector2f{ winWidth, 0.f });
	m_shapeBottom.setOrigin(sf::Vector2f{ 0.f, 0.f });
	m_shapeBottom.setPosition(sf::Vector2f{ winWidth, winHeight });

	m_shapeLeft.setFillColor(fillColor);
	m_shapeLeft.setSize(sf::Vector2f{ 0.f, winHeight });
	m_shapeLeft.setOrigin(sf::Vector2f{ 0.f, 0.f });
	m_shapeLeft.setPosition(sf::Vector2f{ 0.f, 0.f });

	m_shapeRight.setFillColor(fillColor);
	m_shapeRight.setSize(sf::Vector2f{0.f, winHeight});
	m_shapeRight.setOrigin(sf::Vector2f{ 0.f, 0.f });
	m_shapeRight.setPosition(sf::Vector2f{ winWidth, winHeight });

	m_shapeMiddle.setFillColor(sf::Color::Transparent);
	m_shapeMiddle.setOutlineColor(sf::Color{ 200, 0, 0 });
	m_shapeMiddle.setOutlineThickness(3.f);
	m_shapeMiddle.setSize(sf::Vector2f{ winWidth, winHeight });
	m_shapeMiddle.setOrigin(sf::Vector2f{ winWidth, winHeight } / 2.f);
	m_shapeMiddle.setPosition(sf::Vector2f{ winWidth, winHeight } / 2.f);
}

void GamePerimeter::update(float _dt) {
	float aspectRatio = 9.f / 16.f;

	// Shrink perimeter
	float shrinkSpeed = 50.f;
	float shrinkDelta = shrinkSpeed * _dt;

	// Top
	m_shapeTop.setSize(m_shapeTop.getSize() + sf::Vector2f{-shrinkDelta * 2.f, shrinkDelta * aspectRatio });
	m_shapeTop.setPosition(m_shapeTop.getPosition() + sf::Vector2f{ shrinkDelta, 0.f });

	// Bottom
	m_shapeBottom.setSize(m_shapeBottom.getSize() + sf::Vector2f{ -shrinkDelta * 2.f, shrinkDelta * aspectRatio });
	m_shapeBottom.setOrigin(m_shapeBottom.getSize());
	m_shapeBottom.setPosition(m_shapeBottom.getPosition() - sf::Vector2f{ shrinkDelta, 0.f });

	// Left
	m_shapeLeft.setSize(m_shapeLeft.getSize() + sf::Vector2f{ shrinkDelta, 0.f });

	// Right
	m_shapeRight.setSize(m_shapeRight.getSize() + sf::Vector2f{ shrinkDelta, 0.f });
	m_shapeRight.setOrigin(m_shapeRight.getSize());

	// Middle
	m_shapeMiddle.setSize(m_shapeMiddle.getSize() - sf::Vector2f{shrinkDelta * 2.f, shrinkDelta * 2.f * aspectRatio});
	m_shapeMiddle.setOrigin(m_shapeMiddle.getSize() / 2.f);

}

void GamePerimeter::draw() {
	Display::draw(m_shapeTop);
	Display::draw(m_shapeBottom);
	Display::draw(m_shapeLeft);
	Display::draw(m_shapeRight);
	Display::draw(m_shapeMiddle);
}

void GamePerimeter::onCollision(Collider * _this, Collider * _other) {
}

GameObject * GamePerimeter::clone() {
	return new GamePerimeter();
}

void GamePerimeter::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
}
