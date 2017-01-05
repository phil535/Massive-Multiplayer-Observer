#include "PlayerMovementSubjectObserver.h"
#include "Player.h"

/*--------------------------------------------------------------------------------------------------------------------*/
PlayerMovementObserver::PlayerMovementObserver(Player &player) : player_(player)
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
PlayerMovementObserver::REGISTER_RESULT PlayerMovementSubject::registerPlayerMovementObserver(PlayerMovementObserver &observer)
{
  // insert and check if new element
  if(observers_.insert(&observer).second)
  {
    playerRegisterNotification(observer.player_);
    return PlayerMovementObserver::NEW_PLAYER;
  }
  return PlayerMovementObserver::ALREADY_EXISTS;
}

/*--------------------------------------------------------------------------------------------------------------------*/
PlayerMovementSubject::PlayerMovementSubject(Player &player) : player_(player)
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
void PlayerMovementSubject::unregisterPlayerMovementObserver(PlayerMovementObserver &observer)
{
  if(observers_.erase(&observer) != 0)
    playerUnregisterNotification(observer.player_);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void PlayerMovementSubject::notifyPlayerMovementObservers(Distance &delta)
{
  // remove player from observer if out of range
  for (auto it = observers_.begin(); it != observers_.end(); )
  {
    if(!player_.isInRangeOf((*it)->player_))
    {
      (*it)->player_.unregisterPlayerMovementObserver(player_);
      it = observers_.erase(it);
    }
    else
    {
      ++it;
    }
  }

  for(auto observer : observers_)
    observer->playerMovementNotification(this->player_, delta);
}
