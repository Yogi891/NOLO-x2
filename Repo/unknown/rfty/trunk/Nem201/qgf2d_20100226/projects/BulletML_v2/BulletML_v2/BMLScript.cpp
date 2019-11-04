#include "BMLScript.h"
#include "Renderer.h"


const double C_PI = 3.14159265;


BMLScript::BMLScript(std::string a_bMLFile)
: m_dt(0)
, m_delay(0)
, m_bulletAmount(-1)
, m_isPlaying(false)
, m_isScriptAlive(false)
, m_yPos(0)
, m_startTime(0)
{
	pXML = new XMLParser();

	if(!pXML->ParseXML(a_bMLFile))
	{
		std::cout << "Error with BulletML File\n";
	}

	m_bEnemy = new BEnemy(0, 1);

	m_bullets.push_back(m_bEnemy);
	for(int i = 0; i < 50; ++i)
	{	
		CBullet* bullet = new Test_Bullet();
		m_bullets.push_back(bullet);
	}
	for(int i = 0; i < 50; ++i)
	{
		CBullet* bullet = new Test_Bullet();
		m_playingBullets.push_back(bullet);
	}
}

void BMLScript::SetPlayer(Player* a_pPlayer)
{
	m_pPlayer = a_pPlayer;
}

void BMLScript::RunScript(float dt)
{
	m_dt = dt;
	m_delay = 0.0f;
	m_bulletAmount = -1; // .... Since arrays start at 0

	for(int i = 0, size = pXML->GetTags()->size(); i < size; ++i)
	{

		XMLTag* curTag = pXML->GetTags()->at(i);
		if(curTag->GetTagType() == ACTION)
		{
			TagAction* curTagAction = (TagAction*)curTag;
			if(!curTagAction->GetLabel())
			{
				// This tag has no label
				continue;
			}
			std::string label = *curTagAction->GetLabel();
			// Needs to be at least one "top" label
			// can be named as top1, top2, topcool, topnoob, ...
			if(label.find("top") == 0)
			{
				std::cout << "Found Action Top\n";
				

				i += RunAction(i + 1);
				break;
			}
		}
	}
	m_bullets[0]->SetPosition(sf::Vector2f(1290.0f, m_yPos));
}

void BMLScript::ShootBullets(Timeattack& state, float dt)
{
//		int checkPlayable = 0;
//		int readyBullet = 1;
//		while(checkPlayable < m_bulletAmount + 1)
//		{
//			if(!m_playingBullets[checkPlayable]->IsAlive())
//			{
//				m_playingBullets[checkPlayable] = m_bullets[readyBullet];
	//			m_bullets[checkPlayable]->KillBullet();
//				readyBullet++;
//			}
//			checkPlayable++;
//		}
//		m_playingBullets[0] = m_bullets[0];
	m_startTime -= dt;

	if(m_startTime <=0)
	{
		int curBul = 0;
		if(!m_bullets[curBul]->IsAlive())
		{
			m_isScriptAlive = false;
			m_isPlaying = false;
		}
		while((curBul < m_bulletAmount + 1))
		{
			if(m_bullets[curBul]->IsAlive())
			{
				m_bullets[curBul]->SetDelay(m_bullets[curBul]->GetDelay() - dt);

				if((m_bullets[curBul]->GetDelay() <= 0))
				{
					if(m_isScriptAlive) m_bullets[curBul]->SetIsShot(true);

					if(m_bullets[curBul]->GetAimed())
					{
						if(m_isScriptAlive)
						{
							if(curBul > 0)
							{
								sf::Vector2f pos = m_bullets[0]->GetPosition();
								m_bullets[curBul]->SetPosition(pos);
							}
							float direction = (C_PI * m_bullets[curBul]->GetDirection())/180.0f;	

							float x1 = m_bullets[curBul]->GetPosition().x;
							float x2 = m_pPlayer->GetPos().x;
							float y1 = m_bullets[curBul]->GetPosition().y;
							float y2 = m_pPlayer->GetPos().y;

							// SFML has y going down!!!!
							sf::Vector2f first(x1, y1);
							sf::Vector2f second(x2, y2);

							sf::Vector2f final = second - first;
								
							sf::Vector2f normal(1, 0); // normal is in x dir

							float dot = final.x*normal.x + final.y*normal.y;
							float mag = sqrt(fabs((final.x*final.x)+final.y*final.y))*sqrt(fabs((normal.x*normal.x)+(normal.y*normal.y)));
							
							
							direction += acos(dot/mag);
							if(y2 > y1) direction = -direction;

//							m_bullets[curBul]->m_scripts.front().m_dir = direction;

//							m_bullets[curBul]->m_scripts.front().m_isAimed = false;

							m_bullets[curBul]->SetDirection(direction);
							m_bullets[curBul]->SetAimed(false);
						}
					}
					if(m_bullets[curBul]->GetIsShot())
					{
						m_bullets[curBul]->Move(state, dt);
						Renderer::GetInstance().AddDrawable(m_bullets[curBul]->GetDrawable());
					}
				}

			}
			curBul++;
		}
	}

}

int BMLScript::RunFire(int curNum)
{
	m_tags.push("fire");
	bool canLeave = false;
	std::string bulletLabel;
	float direction = 0.0f;

	m_bulletAmount++;

	while(!canLeave)
	{
		XMLTag* curTag = pXML->GetTags()->at(curNum);			
		tagType checkTag = curTag->GetTagType();

		int fireLevel = 0;

		if(fireLevel == 0 || checkTag == FIRE)
		{

			switch(checkTag)
			{
			case DIRECTION:
				{
					if(!m_bullets[m_bulletAmount]->IsAlive())
					{
						// Get direction info				
						TagDirection* curTagDirection = (TagDirection*)curTag;

						bulletLabel = *curTagDirection->GetType();

						// BulletML assumes that at 0 degrees it is pointing straight up
						// and the angle increases in a clockwise direction
						// this is much different from the norm
						// 



						if(bulletLabel == "aim")
						{
							direction = (C_PI * GetContent(curNum))/180.0f;

							m_bullets[m_bulletAmount]->SetDirection(direction);	
							m_bullets[m_bulletAmount]->SetAimed(true);	

	//						m_currentScript.m_dir = direction;
	//						m_currentScript.m_isAimed = true;
						}
						else if(bulletLabel == "absolute")
						{
							// Using BulletML's trigonometry
							//   eg 0 degrees = up & clockwise
							direction = (C_PI * GetContent(curNum))/180.0f;
							direction = -direction + C_PI/2;

							m_bullets[m_bulletAmount]->SetDirection(direction);	
							m_bullets[m_bulletAmount]->SetAimed(false);
		//					m_currentScript.m_dir = direction;
		//					m_currentScript.m_isAimed = false;
						}
					}
				}

				break;
			case SPEED:
			{

				float speed = 0.0f;
				// Get direction info				
				TagSpeed* curTagSpeed = (TagSpeed*)curTag;

				std::string speedLabel = *curTagSpeed->GetType();


				if(speedLabel == "absolute")
				{
//					m_currentScript.m_speed = GetContent(curNum);
					speed = GetContent(curNum);
					m_bullets[m_bulletAmount]->SetSpeed(speed);
				}
				else if(speedLabel == "relative")
				{
//					speed = GetContent(curNum);
//					m_currentScript.m_speed = m_bullets[m_bulletAmount]->m_scripts.front().m_speed + speed;
//					m_currentScript.m_isSpeedRelative = true;
				}
				else if(speedLabel == "sequence")
				{
//					speed = GetContent(curNum);
//					m_currentScript.m_speed = m_bullets[m_bulletAmount]->m_scripts.front().m_speed + speed;
//					m_currentScript.m_isSpeedSequence = true;
				}
				else
				{
					std::cout << "Something failed in ChangeSpeed\n";
				}
			}
			break;
			case BULLET:
				{
					curNum = RunBullet(curNum + 1);
				}
				break;
			case BULLETREF:
				{
					
					TagBulletRef* curTagBulletRef = (TagBulletRef*)curTag;

					if(curTagBulletRef->CheckCloseTag()) break;

					std::cout << "At BulletRef ";
					std::string label;
					if(curTagBulletRef->GetLabel())
					{
						label = *curTagBulletRef->GetLabel();
						std::cout << " label = "<< *curTagBulletRef->GetLabel();
					}
					std::cout << "\n";

					SearchForRefBullet(label);
				}
				break;
			case FIRE:
				{
					TagFire* curTagFire = (TagFire*)curTag;

					if(curTag->CheckCloseTag()) 
					{
						canLeave = true;

						m_tags.pop();
						return curNum;
					}

				}
				break;
			default:
				break;
			}
		curNum++;
		if(canLeave) break;

		}
	}
	return curNum;
}


int BMLScript::RunBullet(int curNum)
{
	m_tags.push("bullet");

	bool canLeave = false;
	
	// set the delay on the bullet
//	m_bullets[m_bulletAmount]->SetDelay(m_delay);

//	m_currentScript.m_delay = m_delay;

	if(!m_bullets[m_bulletAmount]->IsAlive())
	{
		m_bullets[m_bulletAmount]->Reset();
	}
	int bulletLevel = 0;
	while(!canLeave)
	{
		XMLTag* curTag = pXML->GetTags()->at(curNum);
		tagType checkTag = curTag->GetTagType();

		if(bulletLevel == 0 || checkTag == BULLET)
		{

			switch(checkTag)
			{
			case ACTION:
				{
					TagAction* curTagAction = (TagAction*)curTag;
					
					curNum = RunAction(curNum + 1);

				}
				break;
			case BULLET:
				{
					TagBullet* curTagBullet = (TagBullet*)curTag;

					if(curTagBullet->CheckCloseTag())
					{
						m_tags.pop();
						canLeave = true;
						m_bullets[m_bulletAmount]->m_scripts.push(m_currentScript);
						m_currentScript.m_dir = 0;
						m_currentScript.m_dirTime = 0;
						m_currentScript.m_speed = 0;
						m_currentScript.m_speedTime = 0;
						m_currentScript.m_targetDir = 0;
						m_currentScript.m_targetSpeed = 0;

						return curNum;
					}
				}
				break;
			default:
				break;
			}
			curNum++;
			if(canLeave) break;
		}
	}
	return curNum;
}
tagType BMLScript::CheckNextTag(int curNum)
{
	return pXML->GetTags()->at(curNum + 1)->GetTagType();
}
void BMLScript::FindFire(int curNum)
{
	for(int i = curNum, size = pXML->GetTags()->size(); i < size; ++i)
	{
		XMLTag* curTag = pXML->GetTags()->at(i);
		if(curTag->GetTagType() == FIRE)
		{
//			std::cout << "Found Fire\n";
			FindBullet(i);
		}
	}

}

void BMLScript::FindBullet(int curNum)
{
	for(int i = curNum, size = pXML->GetTags()->size(); i < size; ++i)
	{
		XMLTag* curTag = pXML->GetTags()->at(i);
		if(curTag->GetTagType() == BULLET)
		{

		}
		if(curTag->GetTagType() == BULLETREF)
		{
			TagBulletRef* curTagBulletRef = (TagBulletRef*)curTag;

//			std::cout << "Found BulletRef ";
			std::string label;
			if(curTagBulletRef->GetLabel())
			{
				label = *curTagBulletRef->GetLabel();
				std::cout << " label = "<< *curTagBulletRef->GetLabel();
			}
			std::cout << "\n";

			SearchForRefBullet(label);
		}
	}
}


void BMLScript::SearchForRefBullet(std::string a_label)
{
	for(int i = 0, size = pXML->GetTags()->size(); i < size; ++i)
	{
		XMLTag* curTag = pXML->GetTags()->at(i);
		if(curTag->GetTagType() == BULLET)
		{
			TagBullet* curTagBullet = (TagBullet*)curTag;
			if(!curTagBullet->GetLabel())
			{
				// This tag has no label
				continue;
			}
			std::string label = *curTagBullet->GetLabel();
			// Needs to be at least one "top" label
			// can be named as top1, top2, topcool, topnoob, ...
			if(label.find(a_label) == 0)
			{
				std::cout << "Found \"" << a_label << "\" Bullet\n";

				i += RunBullet(i + 1);
			}	
		}
	}	
}

int BMLScript::RunAction(int curNum)
{
	m_tags.push("action");

	bool canLeave = false;

	int actionLevel = 0;

	while(!canLeave)
	{
		XMLTag* curTag = pXML->GetTags()->at(curNum);
		tagType checkTag = curTag->GetTagType();

		if(actionLevel == 0 || checkTag == ACTION)
		{
			switch(checkTag)
			{
			case REPEAT:
				{
					curNum = RunRepeat(curNum);
				}
				break;
			case WAIT:
				{
					RunWait(curNum);
					m_currentScript.m_delay = m_delay;
				}
				break;
			case FIRE:
				{
					curNum = RunFire(curNum + 1);
				}
				break;
			case ACTION:
				{
					TagAction* curTagAction = (TagAction*)curTag;

					if(curTagAction->CheckCloseTag())
					{
						canLeave = true;
						m_tags.pop();
						return curNum;
					}

				}
				break;
			case CHANGEDIRECTION:
				{
					curNum = RunChangeDirection(curNum + 1);
				}
				break;
			case CHANGESPEED:
				{
					curNum = RunChangeSpeed(curNum + 1);
				}
				break;
			default:
				break;
			}
		}
		curNum++;
		if(canLeave) break;
	}	
	return curNum;
}
int BMLScript::RunChangeDirection(int curNum)
{
	m_tags.push("changeDirection");
	bool canLeave = false;

	while(!canLeave)
	{
		XMLTag* curTag = pXML->GetTags()->at(curNum);
		tagType checkTag = curTag->GetTagType();

		switch(checkTag)
		{
		case DIRECTION:
			{

				float direction = 0.0f;
				// Get direction info				
				TagDirection* curTagDirection = (TagDirection*)curTag;

				std::string bulletLabel = *curTagDirection->GetType();

				// BulletML assumes that at 0 degrees it is pointing straight up
				// and the angle increases in a clockwise direction
				// this is much different from the norm
				// 

				if(bulletLabel == "aim")
				{
					direction = (C_PI * GetContent(curNum))/180.0f;

					m_currentScript.m_dir = direction;
					m_currentScript.m_isAimed = true;
					m_currentScript.m_isRelative = false;
					m_currentScript.m_isSequence = false;
				}
				else if(bulletLabel == "absolute")
				{
					// Using BulletML's trigonometry
					//   eg 0 degrees = up & clockwise
					direction = (C_PI * GetContent(curNum))/180.0f;
					direction = -direction + C_PI/2;

					m_currentScript.m_dir = direction;
					m_currentScript.m_isAimed = false;
					m_currentScript.m_isRelative = false;
					m_currentScript.m_isSequence = false;
				}
				else if(bulletLabel == "relative")
				{
					direction = (C_PI * GetContent(curNum))/180.0f;

					m_currentScript.m_dir = m_currentScript.m_targetDir = direction;
					m_currentScript.m_isAimed = false;
					m_currentScript.m_isRelative = true;
					m_currentScript.m_isSequence = false;
				}
				else if(bulletLabel == "sequence")
				{
					direction = (C_PI * GetContent(curNum))/180.0f;

					m_currentScript.m_dir = m_currentScript.m_targetDir = direction;
					m_currentScript.m_isAimed = false;
					m_currentScript.m_isSequence = true;
					m_currentScript.m_isRelative = false;
				}
				else
				{
					std::cout << "Something failed in ChangeDirection\n";
				}
			}
			break;
		case TERM:
			{
				m_currentScript.m_dirTime = GetContent(curNum);
			}
			break;
		case CHANGEDIRECTION:
			{
				TagChangeDirection* curTagChangeDirection = (TagChangeDirection*)curTag;

				if(curTagChangeDirection->CheckCloseTag())
				{
					m_tags.pop();
					canLeave = true;
					return curNum;
				}		
			}
			break;
		default:
			break;
		}
	
		curNum++;
		if(canLeave) break;
	}

	return curNum;
}

int BMLScript::RunChangeSpeed(int curNum)
{
	m_tags.push("changeSpeed");
	bool canLeave = false;

	while(!canLeave)
	{
		XMLTag* curTag = pXML->GetTags()->at(curNum);
		tagType checkTag = curTag->GetTagType();

		switch(checkTag)
		{
		case SPEED:
			{

				float speed = 0.0f;
				// Get direction info				
				TagSpeed* curTagSpeed = (TagSpeed*)curTag;

				std::string speedLabel = *curTagSpeed->GetType();


				if(speedLabel == "absolute")
				{
					m_currentScript.m_speed = GetContent(curNum);
					m_currentScript.m_isSpeedRelative = false;
					m_currentScript.m_isSpeedSequence = false;
				}
				else if(speedLabel == "relative")
				{
					speed = GetContent(curNum);
					m_currentScript.m_speed = m_currentScript.m_targetSpeed = m_bullets[m_bulletAmount]->m_scripts.front().m_speed + speed;
					m_currentScript.m_isSpeedRelative = true;
					m_currentScript.m_isSpeedSequence = false;
				}
				else if(speedLabel == "sequence")
				{
					speed = GetContent(curNum);
					m_currentScript.m_speed = m_currentScript.m_targetSpeed = m_bullets[m_bulletAmount]->m_scripts.front().m_speed + speed;
					m_currentScript.m_isSpeedRelative = false;
					m_currentScript.m_isSpeedSequence = true;

				}
				else
				{
					std::cout << "Something failed in ChangeSpeed\n";
				}
			}
			break;
		case TERM:
			{
				m_currentScript.m_speedTime = GetContent(curNum);
			}
			break;
		case CHANGESPEED:
			{
				TagChangeSpeed* curTagChangeSpeed = (TagChangeSpeed*)curTag;

				if(curTagChangeSpeed->CheckCloseTag())
				{
					m_tags.pop();
					canLeave = true;
					return curNum;
				}		
			}
			break;
		default:
			break;
		}
	
		curNum++;
		if(canLeave) break;
	}

	return curNum;
}
float BMLScript::GetContent(int curNum)
{
	XMLTag* curTag = pXML->GetTags()->at(curNum);

	tagType checkTag = curTag->GetTagType();

	switch(checkTag)
	{
	case TIMES:
		{
			TagTimes* curTagTimes = (TagTimes*)curTag;
			return atoi(curTagTimes->GetContent()->c_str());
		}
		break;
	case WAIT:
		{
			TagWait* curTagWait = (TagWait*)curTag;
			return atof(curTagWait->GetContent()->c_str());
		}
		break;
	case DIRECTION:
		{
			TagDirection* curTagDirection = (TagDirection*)curTag;
			return atof(curTagDirection->GetContent()->c_str());
		}
		break;
	case TERM:
		{
			TagTerm* curTagTerm = (TagTerm*)curTag;
			return atoi(curTagTerm->GetContent()->c_str());
		}
		break;
	case SPEED:
		{
			TagSpeed* curTagSpeed = (TagSpeed*)curTag;
			return atof(curTagSpeed->GetContent()->c_str());
		}
		break;
	default:
		{
			std::cout << "Error: Improper tag usage\n";
			return 0;
		}
		break;
	}
}

float BMLScript::MakeCalculations(std::string a_content)
{
	float result = 0.0f;
	std::string buffer;
	std::string lhs;
	std::string bufferVar;
	
	std::vector<float> terms;
	std::vector<char> opers;

	char oper;

	bool opFlag = false;
	bool checkVar = false;

	
	for(int i = 0, size = a_content.size(); i < size; ++i)
	{		
		if(a_content[i] == '+')
		{
			opers.push_back('+');
			if(!checkVar) terms.push_back(atof(buffer.c_str()));
			checkVar = false;
			buffer.clear();

//			if(opFlag)
//			{
//				if(checkVar)
//				{
//					if(strcmp(buffer.c_str(), "rand") == 0)
//					{
//						float randNum = (float)rand() / (float)RAND_MAX;
//						result = Operation(oper, result, randNum);
//					}
//				}
//				else
//				{
//					result = Operation(oper, result, atof(buffer.c_str()));
//				}
//				char oper = '+';
//				checkVar = false;
//			}
//			else
//			{
//				opFlag = true;
//				result = atof(buffer.c_str());
//				oper = '+';
//				buffer.clear();
//			}
		}
		else if(a_content[i] == '-')
		{
			opers.push_back('-');
			if(!checkVar) terms.push_back(atof(buffer.c_str()));
			checkVar = false;
			buffer.clear();


/*			if(opFlag)
			{
				if(checkVar)
				{
					if(strcmp(buffer.c_str(), "rand") == 0)
					{
						float randNum = (float)rand() / (float)RAND_MAX;
						result = Operation(oper, result, randNum);
					}

				}
				else
				{
					result = Operation(oper, result, atof(buffer.c_str()));
				}
				char oper = '-';
				checkVar = false;
			}
			else
			{
				opFlag = true;
				result =  atof(buffer.c_str());
				oper = '-';
				buffer.clear();
			}
*/

		}
		else if(a_content[i] == '*')
		{
			opers.push_back('*');
			if(!checkVar) terms.push_back(atof(buffer.c_str()));
			checkVar = false;
			buffer.clear();

/*
			if(opFlag)
			{
				if(checkVar)
				{
					if(strcmp(buffer.c_str(), "rand") == 0)
					{
						float randNum = (float)rand() / (float)RAND_MAX;
						result = Operation(oper, result, randNum);
					}

				}
				else
				{
					result = Operation(oper, result, atof(buffer.c_str()));					
				}
				char oper = '*';
				checkVar = false;
			}
			else
			{
				opFlag = true;
				result = atof(buffer.c_str());
				oper = '*';
				buffer.clear();
			}

*/

		}
		else if(a_content[i] == '/')
		{
			opers.push_back('/');
			if(!checkVar) terms.push_back(atof(buffer.c_str()));
			checkVar = false;

			buffer.clear();

/*
			if(opFlag)
			{
				if(checkVar)
				{
					if(strcmp(buffer.c_str(), "rand") == 0)
					{
						float randNum = (float)rand() / (float)RAND_MAX;
						result = Operation(oper, result, randNum);
					}

				}
				else
				{
					result = Operation(oper, result, atof(buffer.c_str()));
				}
				char oper = '/';
				checkVar = false;
			}
			else
			{
				opFlag = true;
				result = atof(buffer.c_str());
				oper = '/';
				buffer.clear();
			}


*/
		}
		else if(a_content[i] == '$' )
		{
			checkVar = true;
		}
		else if(checkVar)
		{
			bufferVar += a_content[i];
		}
		else if(!checkVar && !bufferVar.empty())
		{
			if(strcmp(bufferVar.c_str(), "rand") == 0)
			{
				float randNum = RandomNumber();
				terms.push_back(randNum);
				bufferVar.clear();
			}
			buffer += a_content[i];

		}
		else
		{
//			if(i == 0) opers.push_back('+');
			buffer += a_content[i];
		}


	}
	
	if(checkVar)
	{
		if(strcmp(bufferVar.c_str(), "rand") == 0)
		{
			float randNum = RandomNumber();
			terms.push_back(randNum);
			bufferVar.clear();
		}
	}
	if(!buffer.empty())
	{
		terms.push_back(atof(buffer.c_str()));
		buffer.clear();
	}

	int sizey = terms.size();
	int checkOp = 0;

	std::vector<float> temp;

	for(int i = 0; i < sizey; ++i)
	{
		if(i < sizey - 1)
		{
			if(opers[i] == '/')
			{
				result = Operation('/', terms[i], terms[i+1]);
				temp.push_back(result);
				opers[i] = 'd';
				++i;
				continue;
			}
		}
		temp.push_back(terms[i]);
	}
	while(true)
	{
		if(opers[checkOp] == 'd')
		{
			opers.erase(opers.begin()+checkOp);
		}
		else
		{
			++checkOp;
		}
		if(checkOp == opers.size())
		{
			break;
		}	
	}
	terms = temp;
	temp.clear();

	sizey = terms.size();
	for(int i = 0; i < sizey; ++i)
	{
		if(i < sizey - 1)
		{
			if(opers[i] == '*')
			{
				result = Operation('*', terms[i], terms[i+1]);
				temp.push_back(result);
				opers[i] = 'd';
				++i;
				continue;
			}
		}
		temp.push_back(terms[i]);
	}
	checkOp = 0;
	while(true)
	{
		if(opers[checkOp] == 'd')
		{
			opers.erase(opers.begin()+checkOp);
		}
		else
		{
			++checkOp;
		}
		if(checkOp == opers.size())
		{
			break;
		}	
	}
	terms = temp;
	temp.clear();

	sizey = terms.size();
	for(int i = 0; i < sizey; ++i)
	{
		if(i < sizey - 1)
		{
			if(opers[i] == '+')
			{
				result = Operation('+', terms[i], terms[i+1]);
				temp.push_back(result);
				opers[i] = 'd';
				++i;
				continue;
			}
		}
		temp.push_back(terms[i]);
	}
	checkOp = 0;
	while(true)
	{
		if(opers[checkOp] == 'd')
		{
			opers.erase(opers.begin()+checkOp);
		}
		else
		{
			++checkOp;
		}
		if(checkOp == opers.size())
		{
			break;
		}	
	}
	terms = temp;
	temp.clear();

	sizey = terms.size();
	for(int i = 0; i < sizey; ++i)
	{
		if(i < sizey - 1)
		{
			if(opers[i] == '-')
			{
				result = Operation('-', terms[i], terms[i+1]);
				temp.push_back(result);
				opers[i] = 'd';
				++i;
				continue;
			}
		}
		temp.push_back(terms[i]);
	}
	checkOp = 0;
	while(true)
	{
		if(opers[checkOp] == 'd')
		{
			opers.erase(opers.begin()+checkOp);
		}
		else
		{
			++checkOp;
		}
		if(checkOp == opers.size())
		{
			break;
		}	
	}
	terms = temp;
	temp.clear();

	result = terms[0];

	return result;

}

float BMLScript::Operation(char a_oper, float a_lhs, float a_rhs)
{
	switch(a_oper)
	{
	case '+':
		return a_lhs + a_rhs;
		break;
	case '-':
		return a_lhs - a_rhs;
		break;
	case '*':
		return a_lhs * a_rhs;
		break;
	case '/':
		return a_lhs / a_rhs;
		break;
	default:
		break;
	}

	return 0.0f;
}
float BMLScript::RandomNumber()
{
	return (float)rand() / (float)RAND_MAX;
}
bool BMLScript::RunWait(int curNum)
{
	m_delay += GetContent(curNum)/60.0f;
	m_currentScript.m_delay = m_delay;
	m_bullets[m_bulletAmount]->m_scripts.push(m_currentScript);
	m_currentScript.m_speedTime = 0;
	m_currentScript.m_dirTime = 0;
	return true;
}

int BMLScript::RunRepeat(int curNum)
{
	XMLTag* curTag = pXML->GetTags()->at(curNum);
	TagRepeat* curTagRepeat = (TagRepeat*)curTag;

	tagType checkTag = curTag->GetTagType();

	int repeatTimes = 0;

	if(curTagRepeat->CheckCloseTag())
	{
		m_tags.pop();
		return curNum;
	}
	else
	{
		m_tags.push("repeat");
	}

	// Needs to be followed by <times>
	checkTag = CheckNextTag(curNum);
	if(checkTag != TIMES)
	{
		std::cout << "Error: Expected <times> tag, - disregarded <repeat>\n";
	}
	else
	{
		repeatTimes = (int)GetContent(curNum + 1);
	}

	checkTag = CheckNextTag(curNum + 1);

	// Then need to be followed by an <action>.
	// <repeat> handles everything inside
	// the <action> tag.
	if(checkTag != ACTION)
	{
		std::cout << "Error Expected <action> tag\n";
	}
	else
	{
		int repeatStart = curNum;
		for(int i = 0; i < repeatTimes; ++i)
		{
			curNum = RunAction(repeatStart + 3);
		}
	}
	return curNum;
}

bool BMLScript::IsNowPlaying()
{
	return m_isPlaying;
}

void BMLScript::FireScript(float dt)
{
	if(m_isPlaying)
	{
		return;
	}
	else m_isPlaying = true;
	m_isScriptAlive = true;
//	ShootBullets(dt);
}

void BMLScript::SetEnemyStart(float yPos)
{
	m_yPos = yPos;
}
void BMLScript::SetStartTime(float a_startTime)
{
	m_startTime = a_startTime;
}

BEnemy* BMLScript::GetEnemy()
{

	return (BEnemy*)m_bullets[0];
}

Test_Bullet* BMLScript::GetBullet(int a_num)
{
	if(a_num > m_bullets.size())
	{
		return NULL;
	}

	return (Test_Bullet*)m_bullets[a_num];;
}