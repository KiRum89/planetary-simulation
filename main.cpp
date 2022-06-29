#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>
using namespace std;
struct Vector2
{
	double x = 0;
	double y = 0;
	Vector2() {};
	Vector2(double x,double y)
	{
		this->x = x;
		this->y = y;
	}
	Vector2 operator+(const Vector2& vec){
		Vector2 vec_new;
		vec_new.x = this->x + vec.x;
		vec_new.y = this->y + vec.y;
		return vec_new;
	}	
	Vector2 operator-(const Vector2& vec){
		Vector2 vec_new;
		vec_new.x = this->x - vec.x;
		vec_new.y = this->y - vec.y;
		return vec_new;
	}	
	Vector2 operator*(double c){

		Vector2 vec_new;
		vec_new.x = this->x*c;
		vec_new.y = this->y*c;
		return vec_new;

	}

};

struct Particle
{
	double m{0};
	Vector2 r{0,0};
	Vector2 v{0,0};
	Particle(){};
	Particle(double m, Vector2 r, Vector2 v){
		this->m = m;
		this->r = r;
		this->v = v;	
	}	
};

double abs(const Vector2& vec){
	return sqrt(pow(vec.x,2)+pow(vec.y,2));
}

Vector2 G(Particle p1, Particle p2){
	
	return (p2.r-p1.r)*(p1.m*p2.m/pow(abs(p1.r-p2.r)+1,3));

}

int main()
{

	double s = 0.01;
	double dt = 1e-2;

	Vector2 r0 {200,200};
	Vector2 v0 {-1,1};
	Particle p0(10,r0,v0);	

	Vector2 r1 {100,100};
	Vector2 v1 {-0.1,0.4};
	Particle p1(10,r1,v1);	

	Vector2 r2 {300,300};
	Vector2 v2 {0,-0};
	Particle p2(180,r2,v2);	


	Particle arr[3]{p0,p1,p2};

	//todo: make elastic walls	
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	sf::CircleShape gplanet1;
    while (window.isOpen())
    {

		for (int i=0;i<3;++i){
			arr[i].r = arr[i].r + arr[i].v*dt;	

			for (int j=i+1;j<3;++j){
				arr[i].v =  arr[i].v + G(arr[i],arr[j])*(dt/arr[i].m);
				arr[j].v = arr[j].v + G(arr[j],arr[i])*(dt/arr[j].m);
			}
		}
		for (int i=0;i<3;++i){
			sf::CircleShape c;
			c.setRadius(1);
			c.setPosition(arr[i].r.x,arr[i].r.y);
			window.draw(c);
		}
        sf::Event event;
        while (window.pollEvent(event))
        {
             if (event.type == sf::Event::Closed)
                window.close();
        }
		//window.draw(gplanet1);
		//window.draw(gsun);
		window.display();
	}
	return 0;
}
