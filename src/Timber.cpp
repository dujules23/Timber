// include important libraries here
#include <SFML/Graphics.hpp>
#include <iostream>

// make code easier to type with "using namespace" using namespace sf;

using namespace sf;

 // Helper function to load a texture from a file and handle errors

 Texture loadTexture(const std::string& path) {
    Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "ERROR: Could not load texture: " << path << "\n";
        exit(EXIT_FAILURE);
    }
    return texture;
}

// this is where our game starts from int main()

int main()
{
  
  // create a video mode object (SFML 3 uses a Vector2u constructor)
  VideoMode vm({1680, 1050});

  // create and open a window for the game
  // use windowed mode for now (debugging)
  RenderWindow window(vm, "Timber!!!");


  // Create a texture to hold a graphic on the GPU Texture
  Texture textureBackground = loadTexture("graphics/background.png");


  // Create a sprite, Attach the texture to the sprite

  Sprite spriteBackground(textureBackground);

  // Set the spriteBackground to cover the screen
  spriteBackground.setPosition({0, 0});

  // Make a tree sprite
  Texture textureTree = loadTexture("graphics/tree.png");
  Sprite spriteTree(textureTree);
  spriteTree.setPosition({700, 0});

  // Prepare the Bee sprite
  Texture textureBee = loadTexture("graphics/bee.png");
  Sprite spriteBee(textureBee);
  spriteBee.setPosition({0, 800});

  // Is the bee currently moving?
  bool beeActive = false;

  // How fast can the bee fly?
  float beeSpeed = 0.0f;

  // make 3 cloud sprites from 1 texture
  Texture textureCloud = loadTexture("graphics/cloud.png");
  Sprite spriteCloud1(textureCloud);
  Sprite spriteCloud2(textureCloud);
  Sprite spriteCloud3(textureCloud);

  // Position the clouds on the left of the screen at different heights
  spriteCloud1.setPosition({0, 0});
  spriteCloud2.setPosition({0, 150});
  spriteCloud3.setPosition({0, 300});

  // Are the clouds currently on screen?
  bool cloud1Active = false;
  bool cloud2Active = false;
  bool cloud3Active = false;

  // How fast is each cloud?
  float cloud1Speed = 0.0f;
  float cloud2Speed = 0.0f;
  float cloud3Speed = 0.0f;

  // Variables to control time itself
  Clock clock;

  while (window.isOpen())
  {
    /* Handle the player's input*/
    // poll event needed for MacOS, otherwise the window will freeze when you click the close button
    while (const auto event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
      {
        window.close();
      }
      else if (event->is<sf::Event::KeyPressed>())
      {
        const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();
        if (keyEvent && keyEvent->code == Keyboard::Key::Escape)
        {
          window.close();
        }
      }
    }

    /* Update the scene*/

    // Clear everything from the last frame
    window.clear();

    // Measure Time, Dt stands for delta time, the time between updates
    Time dt = clock.restart();

    // Setup the bee
    if(!beeActive)
    {
      // How fast is the bee?
      srand((int)time(0));
      beeSpeed = (rand() % 200) + 200;

      // How high is the bee?
      srand((int)time(0) * 10);
      float height = (rand() % 500) + 500;
      spriteBee.setPosition({2000, height});
      beeActive = true;
    }
    else
    {
      // move the bee
      // SFML 3 uses Vector2f for positions, so we need to get the current position, modify it, and set it back
      sf::Vector2f pos = spriteBee.getPosition();
      pos.x -= beeSpeed * dt.asSeconds();
      spriteBee.setPosition(pos);

      // has the bee reached the left-hand edge of the screen?
      if(spriteBee.getPosition().x < -100)
      {
        // set it up ready to be a whole new bee next frame
        beeActive = false;
      }
    }

    // Manage the clouds
    // Cloud 1
    if(!cloud1Active)
    {
      // How fast is the cloud?
      srand((int)time(0) * 10);
      cloud1Speed = (rand() % 200);

      // how high is the cloud
      srand((int)time(0) * 10);
      float height = (rand() % 150);
      spriteCloud1.setPosition({-200, height});
      cloud1Active = true;
    }else
    {
      // Move the cloud
      sf::Vector2f pos = spriteCloud1.getPosition();
      pos.x += cloud1Speed * dt.asSeconds();
      spriteCloud1.setPosition(pos);

      // Has the cloud reached the right-hand edge of the screen?
      if(spriteCloud1.getPosition().x > 1920)
      {
        // Set it up ready to be a whole new cloud next frame
        cloud1Active = false;
      }
    }

    // Cloud 2
    if(!cloud2Active)
    {
      // How fast is the cloud?
      srand((int)time(0) * 20);
      cloud2Speed = (rand() % 200);

      // how high is the cloud
      srand((int)time(0) * 20);
      float height = (rand() % 300) - 150;
      spriteCloud2.setPosition({-200, height});
      cloud2Active = true;
    }
    else
    {
      // Move the cloud
      sf::Vector2f pos = spriteCloud2.getPosition();
      pos.x += cloud2Speed * dt.asSeconds();
      spriteCloud2.setPosition(pos);

      // Has the cloud reached the right-hand edge of the screen?
      if(spriteCloud2.getPosition().x > 1920)
      {
        // Set it up ready to be a whole new cloud next frame
        cloud2Active = false;
      }
    }

    // Cloud 3
    if(!cloud3Active)
    {
      // How fast is the cloud?
      srand((int)time(0) * 30);
      cloud3Speed = (rand() % 200);

      // how high is the cloud
      srand((int)time(0) * 30);
      float height = (rand() % 450) - 150;
      spriteCloud3.setPosition({-200, height});
      cloud3Active = true;
    }
    else
    {
      // Move the cloud
      sf::Vector2f pos = spriteCloud3.getPosition();
      pos.x += cloud3Speed * dt.asSeconds();
      spriteCloud3.setPosition(pos);

      // Has the cloud reached the right-hand edge of the screen?
      if(spriteCloud3.getPosition().x > 1920)
      {
        // Set it up ready to be a whole new cloud next frame
        cloud3Active = false;
      }
    }


    // Draw our game scene here
    window.draw(spriteBackground);

    // Draw the clouds
    window.draw(spriteCloud1);
    window.draw(spriteCloud2);
    window.draw(spriteCloud3);

    // Draw the tree
    window.draw(spriteTree);

    // Draw the bee
    window.draw(spriteBee);

    // show everything we just drew
    window.display();
  }

  

    return 0;
}