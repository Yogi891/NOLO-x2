#include "qgf2d/gameobject.h"

namespace
{
	long long g_maxId=0;
}


namespace qgf
{

	namespace GameWorld
	{
		const int c_divisions = 10;

		std::map<long long, GameObject *> worldObjects;
		long long worldHighestID = 0;
		kf::Vector2 worldGravity(0,0);

		kf::Vector2 gravity()
		{
			return worldGravity;
		}
		void gravity(const kf::Vector2 &grav)
		{
			worldGravity = grav;
		}
		long long newID()
		{
			return ++worldHighestID;
		}
		void update(float dt)
		{
			std::vector<long long> deadobjects;
			for(std::map<long long, GameObject *>::iterator it = worldObjects.begin(); it!= worldObjects.end(); ++it)
			{
				it->second->update(dt);
				if(it->second->m_dead)
				{
					deadobjects.push_back(it->first);
				}
			}


			if(CollisionCallback)
			{
				std::vector<GameObject *> cells[c_divisions][c_divisions];

				int cx = 0;
				int cy = 0;
				int dx = 800/c_divisions;
				int dy = 600/c_divisions;

				for(std::map<long long, GameObject *>::iterator it = worldObjects.begin();it != worldObjects.end();it++)
				{
					if(it->second->m_collide && !it->second->m_dead)
					{
						int sx = (it->second->m_position.x - it->second->m_sprite->GetSize().x * 0.5)/dx;
						int sy = (it->second->m_position.y - it->second->m_sprite->GetSize().y * 0.5)/dy;
						int ex = (it->second->m_position.x + it->second->m_sprite->GetSize().x * 0.5)/dx;
						int ey = (it->second->m_position.y + it->second->m_sprite->GetSize().y * 0.5)/dy;
						for(int y=sy;y<=ey;y++)
						{
							for(int x=sx;x<=ex;x++)
							{
								if(x>=0 && x< c_divisions && y>=0 && y<c_divisions)
								{
									cells[y][x].push_back(it->second);
								}
							}
						}
					}
				}
				for(int y=0;y<c_divisions;y++)
				{
					for(int x=0;x<c_divisions;x++)
					{
						for(int i=0;i<cells[y][x].size();i++)
						{
							for(int j=i;j<cells[y][x].size();j++)
							{
								if(i!=j && !cells[y][x][i]->m_dead && !cells[y][x][j]->m_dead)
								{
									if(cells[y][x][i]->m_position.x + cells[y][x][i]->m_sprite->GetSize().x * 0.35f > cells[y][x][j]->m_position.x - cells[y][x][j]->m_sprite->GetSize().x * 0.35f
										&& cells[y][x][i]->m_position.x - cells[y][x][i]->m_sprite->GetSize().x * 0.35f < cells[y][x][j]->m_position.x + cells[y][x][j]->m_sprite->GetSize().x * 0.35f
										&& cells[y][x][i]->m_position.y + cells[y][x][i]->m_sprite->GetSize().y * 0.35f > cells[y][x][j]->m_position.y - cells[y][x][j]->m_sprite->GetSize().y * 0.35f
										&& cells[y][x][i]->m_position.y - cells[y][x][i]->m_sprite->GetSize().y * 0.35f < cells[y][x][j]->m_position.y + cells[y][x][j]->m_sprite->GetSize().y * 0.35f)
									{
										CollisionCallback(cells[y][x][i],cells[y][x][j]);
									}
								}
							}
						}
					}
				}
			}


			for(unsigned int i=0;i<deadobjects.size();++i)
			{
				std::map<long long, GameObject *>::iterator it = worldObjects.find(deadobjects[i]);
				if(it!=worldObjects.end())
				{
					delete it->second;
					worldObjects.erase(it);
				}
			}
		}
		void render(sf::RenderWindow *rw)
		{
			for(std::map<long long, GameObject *>::iterator it = worldObjects.begin(); it!= worldObjects.end(); ++it)
			{
				it->second->render(rw);
			}
		}
	}


	void GameObject::update(float dt)
	{
		if(m_life>0)
		{
			m_life-=dt;
			if(m_life<=0)
			{
				m_dead = true;
				return;
			}
		}
		if(m_physicsStyle == e_psNewtonian)
		{
			if(m_gravity)
				m_velocity += GameWorld::gravity()*dt;
			m_velocity += m_force * dt;
			m_position+=m_velocity * dt;
			m_force.set(0,0);
			if(m_position.y>600)
			{
				m_position.y = 600;
				m_velocity.y = -fabs(m_velocity.y)*0.7;
			}
		}
		if(m_physicsStyle == e_psBox2D)
		{
			m_position.set(m_body->GetPosition().x, 600-m_body->GetPosition().y);
			m_rotation = m_body->GetAngle();
		}
		if(m_type==1)
			m_rotation = atan2(-m_velocity.x,-m_velocity.y);
	}

	void GameObject::render(sf::RenderWindow *rw)
	{
		if(m_sprite)
		{
			m_sprite->SetPosition(m_position.x, m_position.y);
			m_sprite->SetRotation(m_rotation*57.29);
			rw->Draw(*m_sprite);
			m_overlap = false;
		}
	}

	GameObject::GameObject()
	{
		m_life = 0;
		m_dead = false;
		m_position.set(0,0);
		m_velocity.set(0,0);
		m_force.set(0,0);
		m_physicsStyle = e_psNone;
		m_sprite = 0;
		m_id = 0;
		m_collide = true;
		m_body = 0;
		m_rotation = 0;
		m_overlap=false;
		m_gravity = true;
		m_type = 0;
	}

	GameObject::~GameObject()
	{
		if(m_body)
		{
			m_body->GetWorld()->DestroyBody(m_body);
			m_body = 0;
		}
		delete m_sprite;
		m_sprite = 0;
	}

	GameObject *GameObject::build()
	{
		return new GameObject;
	}

	GameObject &GameObject::position(const kf::Vector2 &pos)
	{
		m_position = pos;
		if(m_physicsStyle == e_psBox2D)
		{
			m_body->SetXForm(b2Vec2(m_position.x,600-m_position.y),m_rotation);
		}

		return *this;
	}

	GameObject &GameObject::velocity(const kf::Vector2 &vel)
	{
		m_velocity = vel;
		if(m_physicsStyle == e_psBox2D)
		{
			m_body->SetLinearVelocity(b2Vec2(m_velocity.x,-m_velocity.y));
		}
		return *this;
	}

	GameObject &GameObject::addForce(const kf::Vector2 &force)
	{
		m_force += force;
		if(m_physicsStyle == e_psBox2D)
		{
			m_body->ApplyForce(b2Vec2(force.x,-force.y),b2Vec2(0,0));
		}
		return *this;
	}

	kf::Vector2 GameObject::position()
	{
		return m_position;
	}

	kf::Vector2 GameObject::velocity()
	{
		return m_velocity;
	}

	ObjectTemplate::ObjectTemplate()
	{
	}

	ObjectFactory::ObjectFactory()
	{
	}

	ObjectFactory::~ObjectFactory()
	{
	}

	GameObject *ObjectFactory::addObject(const std::string name)
	{
		GameObject *gob = 0;
		std::map<std::string, ObjectTemplate>::iterator it = m_objectTemplates.find(name);
		if(it!=m_objectTemplates.end())
		{
			gob = it->second.m_buildFunc();
			sf::Image *im = getImage(it->second.m_imageName);
			if(im)
			{
				gob->m_sprite = new sf::Sprite(*im);
				gob->m_sprite->SetSubRect(sf::IntRect(it->second.m_corner1.x,it->second.m_corner1.y, it->second.m_corner2.x, it->second.m_corner2.y));
				gob->m_sprite->SetCenter(it->second.m_centre.x, it->second.m_centre.y);
			}
			else
			{
				gob->m_sprite = 0;
			}
			gob->m_type = it->second.m_type;
			gob->m_life = it->second.m_life;
			gob->m_gravity = it->second.m_gravity;
			gob->m_physicsStyle = GameObject::e_psNewtonian;
			long long id = GameWorld::newID();
			gob->m_id = id;
			GameWorld::worldObjects[id] = gob;
		}
		return gob;
	}

	sf::Image *ObjectFactory::getImage(const std::string &filename)
	{
		std::map<std::string, sf::Image *>::iterator it= m_images.find(filename);
		if(it==m_images.end())
		{
			sf::Image *im = new sf::Image;
			if(!im->LoadFromFile(filename))
			{
				delete im;
				return 0;
			}
			m_images[filename] = im;
			return im;
		}
		return it->second;
	}


	CollisionCallback_t CollisionCallback = 0;
	ObjectFactory g_objectFactory;
}
