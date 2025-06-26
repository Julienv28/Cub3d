# Cub3d

A 42 Version of Wolfenstein, a bit less interactive and constructed, but aimed to discover RayCasting !

## What is RayCasting ?
### Mathematical Considerations*

First, let's go on definitions. RayCastinng is a calculation technique applied on pictures for 3D rendering ([Wikipedia](https://fr.wikipedia.org/wiki/Raycasting) defines it better).
Then, once we understand these basics, let's go on the mathematical part. To understand it, we must know that, by proportionnality, a height A on a distance 1 will be as proportionnaly high as a height B on distance 2. So that :

$$\frac{h_1}{d_1} = \frac{h_2}{d_2}$$

As we are looking at the height $$h_m$$ of a wall with respect to $$h_s$$, the size of the screen, the distance $$d$$ is applied to the same laws. Our expression is : 

$$\frac{h_s}{d_s} = \frac{h_w}{d_w}$$

rearranging the terms, the perceived height($$h_p$$) will be :

$$h_p = d_s\frac{h_m}{d_m}$$

$$h_m$$ and $$d_e$$ are already known as we define these constants beforehand. We are only missing $$d_w$$. The vision of the player will be defined as a part of a circle (FOV) and will cast one ray per number of columns. So the distance will be different between each columns. Logically, if our character faces a wll, the distance will be shorter in the middle than on the peripheries.
To get the distance we only must get to a basic application of the Pythagora theorem with the hypothenus being our distance and the two other sides being the distance betwen the coordinates $$x$$ and $$y$$ of both the player($$x_1,y_1$$) and the obstacle ($$x_2, y_2$$). Consequently :

$$d_w^2 = (x_1 - x_2)^2 + (y_1 - y_2)^2$$

So,

$$d_w = \sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}$$

We are almost perfect, with only a detail : applying it gives a fisheye effect ! To correct it we need to include the player's perspective angle. So that the distance must be corrected applyint the cosinus of the angle of vision (let's call it $$a$$).

To conclude, rearranging all these considerations :

$$h_p = cos_a(d_e\frac{h_m}{\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}})$$

And now you have the whole theory on how to apply your RayCasting ! ;-)

### Applied to code

First, we must define our constant in the .h file using macros. We first defined a screen size 1500 x 1000 pixels (so 1500 rays of a size 1000 pixels) and a tile size at 5 (the smaller, the better the render will be). Of course these choice are purely arbitrary. You may use other dimensions that would be more suitable to your machines. It's entirely up to you.

## Tips and extras



## Sources Used for this project
- 42 Subject
- The original Game : http://users.atw.hu/wolf3d/
- The basics of Cub3d and Raycasting : https://ismailassil.medium.com/ray-casting-c-8bfae2c2fc13
- How Doom and Wolfenstein Posted did their graphism (good introduction to Ray Casting, in french) : https://guy-grave.developpez.com/tutoriels/jeux/doom-wolfenstein-raycasting/
- A concise and easy-to-handle guide for cub3D : https://hackmd.io/@nszl/H1LXByIE2#Camera-plane-vector

*I am not a maths teacher, I am only sharing my pure understanding of the theory. I may be mistaken over some points, don't hesitate to contact me if you want to teach me more precisely how it works
