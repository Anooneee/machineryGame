#include "cond.h"

/*
Enemy front-down-ray facing no h-floor (aka platform edge) -> direction flip
Enemy front-ray facing v-wall -> direction flip
Sword hit box contact enemy hit box -> Enemy disappears 
In air (inquire floor detects no floor) -> fall according to gravity 
Player detects harmful object in the hurt box collision -> resets the program 

Event Name
    Trigger Condition                   
        Description
Bottom of Player Character Floor Collision          
        Bottom edge of player hitbox is less than or equal to top edge of floor box if vertical_velocity is negative
            The player characters vertical_velocity is updated to 0

Top of Player Character Floor Collision
    Top edge of player hitbox is greater than or equal to the top edge of floor box if player vertical_velocity is positive
        The player characters vertical_velocity is updated to 0

Player Character Gravity
    The players character Grounded flag is 0, and vertical_velocity is 0
        Player characters vertical_velocity is decreased by 5 pixels/second

Player Character Right Wall Collision 
    Player Characters right edge is greater than or equal to the left edge of wall box
        Player characters positive horizontal_velocity is updated to 0

Player Character Left Wall Collision
    Player Characters left edge is less than or equal to the right edge of wall box
        Player characters negative horizontal_velocity is updated to 0
Right Edge of Player Character and Enemy Collision

    The right edge of the player hitbox is greater than or equal to the left edge of the Enemy hitbox and the bottom of the Player character bottom edge is less than or equal to the top edge of the Enemy hitbox or the top edge of the player hitbox is greater than or equal to the bottom edge of the enemy hitbox
        Game end flag is updated

Left Edge of Player Character and Enemy Collision
    The left edge of the player hitbox is less than or equal to the right edge of the Enemy hitbox and the bottom of the Player character bottom edge is less than or equal to the top edge of the Enemy hitbox or the top edge of the player hitbox is greater than or equal to the bottom edge of the enemy hitbox
        Game end flag is updated

Right of Player Character and Door Collision
    Bottom edge of player character is greater than or equal to bottom of doorway, top edge of player character is less than or equal to the doorway and right edge of player hitbox is greater than or equal to left edge of doorway hitbox
        Increments Room Selector integer

Left of Player Character and Door Collision
    Bottom edge of player character is greater than or equal to bottom of doorway, top edge of player character is less than or equal to the doorway and left edge of player hitbox is greater than or equal to right edge of doorway hitbox
        Increments Room Selector integer
        
Player Character and Trap Collision
    Bottom of player character hitbox is less than or equal to top edge of trap hitbox and left edge of player character hitbox > right edge of trap < right edge of trap, or right edge of player character hitbox > left edge of trap < right edge of trap
        Game end flag is updated

Attack and Enemy Collision
    Detect player sword hitbox within the body (The right edge of the enemy hitbox is greater than or equal to the left edge of the sword hitbox and the bottom of the enemy character bottom edge is less than or equal to the top edge of the sword hitbox or the top edge of the enemy hitbox is greater than or equal to the bottom edge of the sword hitbox)
        Death animation and sound is started

Bottom of Enemy and Floor Collision
    Front bottom edge of enemy hitbox hit no floor
        Enemy horizontal_velocity is updated by multiplying *-1

Top of Enemy and Floor Collision
    Top edge of enemy hitbox is greater than or equal to the top edge of floor box if enemy vertical_velocity is positive

Enemy Left Wall Collision
    Enemy box  left edge is less than or equal to the right edge of wall box
        Enemy positive horizontal_velocity is updated to 1

Enemy Right Wall Collision
    Enemy box right edge is greater than or equal to the left edge of wall box
        Enemy positive horizontal_velocity is updated to -1



*/