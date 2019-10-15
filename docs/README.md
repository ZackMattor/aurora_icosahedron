# documentation

## Definitions

[**Convex regular icosahedron**](https://en.wikipedia.org/wiki/Icosahedron) - A geometric term for a polyhedron with 20 similar sides. Each surface is a perfect equalateral triangle. A common accurance of an Regular Icosahedron is a 20 sided die. A non-regular Icosahedron can take many shapes - but for all purposes in this document Icosahedron is refering to a Convex regular icosahedron.

**Aurora** - Pet project of Zack Mattor - basically a framework for playing with colored lighting and lighting controllers.

**Aurora Icosahedron** - A lamp that is an Icosahedron with each surface being an individually addressable RGB LED.

## The Projection
I realized if i wanted to do animations across the Icosahedron Light I would need some kind of map to find my way around the object. I derived the following projection as my map. It took some iterations and imagination but I really like conceptualizing the shape in this manner. I found some other projections online but I didn't think they fit my requirements to navigate around the shape.

![Icosahedron Projection](./icosahedron_projection.jpeg?raw=true "Icosahedron Projection")

## Mappings
Using the above projection I derived the following data. Both of the static structures are needed to construct animations for the Aurora Icosahedron. You can tweak them if you want to support other shapes / hardware layouts.

The following surface neighbor mapping is needed to transverse the Icosahedron. Imagine you are walking on the surface of an Icosahedron - and you have the projection map that exists in this folder. The folling data will allow you to know the ID of the surfaces surrounding you. Even better because they are in clockwise order you will be able to know what is to the left and right of you if you are aware of the surface ID that you came from.

An example on how the data can be used is if you are on surface ID 1 and you just moved one surface over to surface ID 2 and you want to know what surfaces are to the left and right of your current direction. You can find the neighbors for surface 2 by the comments on the right of the neighbor lists. So for surface 2 it would be `{ 7, 3, 1 }`. Knowing these are in clockwise order and also knowing that you came from surface 1 you can then derive what is left in right by taking the remainding numbers and mapping them to [ left, right ]. So in this case you remove 1 and you have ` { 7, 3 }` so to your left would be surface 7 and to your right would be surface 3.

It must be known that this is a circular sructure. So if you are on surface 20 and just came from surface 14 left is always the next index in the neighbor mapping. So `{16, 14, 19}` turns into `{19, 16}` so left would be surface 19, and right would be surface 16.

```
static const char icosahedron_neighbors[20][3] = {
  { 15,  2, 5 },    // 1
  { 7, 3, 1 },      // 2
  { 2, 9, 4 },      // 3
  { 5, 3, 11 },     // 4
  { 1, 4, 13 },     // 5
  { 16,  7, 15 },   // 6
  { 6, 8, 2 },      // 7
  { 7, 17,  9 },    // 8
  { 8, 10,  3 },    // 9
  { 9, 18,  11 },   // 10
  { 4, 10,  12 },   // 11
  { 13,  11,  19 }, // 12 
  { 14,  5, 12 },   // 13
  { 20,  15,  13 }, // 14
  { 6, 1, 14 },     // 15
  { 20,  17,  6 },  // 16
  { 16,  18,  8 },  // 17
  { 10,  17,  19 }, // 18
  { 20,  12,  18 }, // 19
  { 16,  14,  19 }  // 20
};
```

The next needed mapping is the mapping between the surface ID and the index of the LED that resides under the surface. This allows the wirring to not match the projection mapping. If you want to light up the projection surface ID of 13 the following will tell you that you need to light up LED number 9.

```
static const char map_icosahedron_hardware[20] = {
  1,  // 1
  5,  // 2
  6,  // 3
  7,  // 4
  8,  // 5
  3,  // 6
  4,  // 7
  19, // 8
  20, // 9
  15, // 10
  14, // 11
  13, // 12
  9,  // 13
  10, // 14
  2,  // 15
  17, // 16
  18, // 17
  16, // 18
  12, // 19
  11  // 20
};
```
