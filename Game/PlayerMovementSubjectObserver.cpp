#include "PlayerMovementSubjectObserver.h"
#include "Player.h"

/*--------------------------------------------------------------------------------------------------------------------*/
PlayerMovementObserver::PlayerMovementObserver(Player &player) : player_(player)
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
PlayerMovementObserver::REGISTER_RESULT PlayerMovementSubject::registerPlayerMovementObserver(PlayerMovementObserver &observer)
{
  // insert and notify if new element
  auto new_element = observers_.insert(&observer).second;
  if(new_element)
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
  // remove observer and notify only if observer was present
  if(observers_.erase(&observer) != 0)
    playerUnregisterNotification(observer.player_);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void PlayerMovementSubject::notifyPlayerMovementObservers(Distance &delta)
{
  for (auto it = observers_.begin(); it != observers_.end(); )
  {
    // remove player from observer if out of range
    if(!player_.isInRangeOf((*it)->player_))
    {
      (*it)->player_.playerUnregisterNotification(player_);
      (*it)->player_.observers_.erase(&player_);

      playerUnregisterNotification((*it)->player_);
      it = observers_.erase(it);
    }
    else
    {
      // otherwise notify observer about player movement
      (*it)->playerMovementNotification(player_, delta);
      ++it;
    }
  }
}
