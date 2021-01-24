# snakegame
snake game windows console app with std::cin and std::cout C++

<p align="left">
  <img src="snake.gif" width = "600" height = "360"/>
</p>

# Idea

I build this game without any graphic library, even graphics.h, just use std::cin and cout to draw.  
I use two threads, one for capturing keyboard input (for moving) and another for movement.  
Whenever a key is pressed, it will be saved to the queue and the movement thread will define what is next movement based on the element of this queue.  
The code is easy to understand I think, and ya, I'm pretty lazy to write so if you guys have any question, just let me know at issues tag ^^.  
