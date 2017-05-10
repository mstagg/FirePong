#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Init fullsize window
    sf::RenderWindow window(sf::VideoMode(200, 200), "FirePong", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    int yMin = 0;
    int yMax = window.getSize().y;
    int xMin = 0;
    int xMax = window.getSize().x;
    std::cout << yMax << std::endl;
    int rate = 10;
    int paddleY = 150;

    sf::Vector2i ballVector(10, 10);

    sf::RectangleShape paddle;
    paddle.setSize(sf::Vector2f(100, 300));
    paddle.setPosition(0, 50);
    paddle.setFillColor(sf::Color::Yellow);

    sf::CircleShape ball(50);
    ball.setPosition(500, 500);
    ball.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        int ballX = ball.getPosition().x + ballVector.x;
        int ballY = ball.getPosition().y + ballVector.y;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            paddleY -= rate;
            paddleY = (paddleY < yMin) ? yMin : paddleY;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            paddleY += rate;
            paddleY = (paddleY > yMax - 300) ? yMax - 300 : paddleY;
        }

        // check collision with walls
        if(ballY < 0)
        {
            ballVector.y *= -1;
        }
        else if (ballY > yMax - 100)
        {
            ballVector.y *= -1;
        }
        if(ballX < 0)
        {
            ballX = 1000;
            ballY = 500;
        }
        else if(ballX > xMax - 100)
        {
            ballVector.x *= -1;
        }

        // check collision with paddle
        if(ballX < 100 && ballY > paddleY && ballY < paddleY + 300)
        {
            ballVector.x *= -1;
        }

        window.clear();
        paddle.setPosition(0, paddleY);
        ball.setPosition(ballX, ballY);
        window.draw(paddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}
