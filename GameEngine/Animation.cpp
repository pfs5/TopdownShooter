#include "Animation.h"
#include "ConfigManager.h"
#include "Debug.h"
#include "json.h"
#include <fstream>
#include "ResourceManager.h"
#include "Rendering.h"
#include "AnimationObserver.h"

Animation::Animation(const std::string & name) :
	_currentFrame{0u},
	_timer{0.f},
	_isPlaying{false}
{
	std::string path = ConfigManager::getInstance().getString("data-paths", "animations-folder") + name + ".anim";
	if (!path.empty())
	{
		loadAnimation(path);
	}
	else
	{
		Debug::logError("[Animation] Error loading animation " + name);
	}
}

void Animation::update(float _dt)
{
	if (_isPlaying)
	{
		_timer += _dt;

		if (_timer > _frameTimes[_currentFrame])
		{
			if (_currentFrame >= _frameTimes.size() - 1)
			{
				reset();
				_isPlaying = _looping;
				notifyOnAnimationEnd();
			}
			else
			{
				++_currentFrame;
				setCurrentFrame();
			}
		}
	}
}

void Animation::draw()
{
	Rendering::draw(_sprite);
}

void Animation::setSpeed(float speed)
{
	for (auto &ft : _frameTimes) {
		ft *= _speed;   // undo current speed setting
		ft /= speed;    // apply new speed setting
	}

	_speed = speed;
}

void Animation::setSize(const sf::Vector2f &size)
{
	sf::Vector2f scale
	{
		size.x / _frameWidth,
		size.y / _frameHeight
	};

	_sprite.setScale(scale);
}

void Animation::setColor(const sf::Color &color)
{
	_sprite.setColor(color);
}

void Animation::setPosition(const sf::Vector2f &position)
{
	_sprite.setPosition(position);
}

void Animation::setRotation(float rotation)
{
	_sprite.setRotation(rotation);
}

bool Animation::isLooping() const
{
	return _looping;
}

void Animation::setIsLooping(bool value)
{
	_looping = value;
}

void Animation::play()
{
	_isPlaying = true;
}

void Animation::stop()
{
	_isPlaying = false;
	reset();
}

void Animation::pause()
{
	_isPlaying = false;
}

void Animation::attachObserver(AnimationObserver *_o)
{
	_observers.push_back(_o);
}

void Animation::dettachObserver(AnimationObserver *_o)
{
	_observers.erase(std::remove(_observers.begin(), _observers.end(), _o), _observers.end());
}

void Animation::loadAnimation(const std::string& path)
{
	std::ifstream file{ path };

	if (file.is_open()) 
	{
		nlohmann::json data;
		file >> data;

		// Data
		std::string name = data["name"];
		std::string spritesheetName = data["spritesheet_path"];
		int rows = data["spritesheet_rows"];
		int cols = data["spritesheet_cols"];
		std::vector<float> frames;
		for (auto& f : data["frames"])	
		{
			frames.push_back(f);
		}
		float speed = data["speed"];
		bool looping = data["looping"];

		// Load animation
		_name = name;
		_spritesheet = ResourceManager::getTextureStatic(spritesheetName);
		_rows = rows;
		_cols = cols;
		_frameTimes = frames;
		_speed = speed;
		_looping = looping;

		_frameWidth = static_cast<float>(_spritesheet->getSize().x) / cols;
		_frameHeight = static_cast<float>(_spritesheet->getSize().y) / rows;

		// Apply speed
		for (auto &ft : _frameTimes)
		{
			ft /= speed;
		}

		_sprite.setTexture(*_spritesheet);
		_sprite.setOrigin(_frameWidth / 2.f, _frameHeight / 2.f);

		setCurrentFrame();

		return;
	}

	Debug::logError("[Animation] Error loading animation from " + path);
}

void Animation::setCurrentFrame()
{
	unsigned int curRow = _currentFrame / _cols;
	unsigned int curCol = _currentFrame % _cols;

	// Set texture rect
	_sprite.setTextureRect(sf::IntRect
	{
		static_cast<int>(curCol * _frameWidth),
		static_cast<int>(curRow * _frameHeight),
		static_cast<int>(_frameWidth),
		static_cast<int>(_frameHeight)
	});
}

void Animation::reset()
{
	_currentFrame = 0u;
	_timer = 0.f;
	setCurrentFrame();
}

void Animation::notifyOnAnimationEnd()
{
	for (auto &o : _observers) {
		o->onAnimationEnd();
	}
}
