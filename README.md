<h1 align="center">
    <div align="center">
      BUAS - Intake Project
    </div>
    <img src="https://img.shields.io/badge/license-MIT*-yellowgreen" height=20 align="right" />
</h1>


<div align="center">
  <b>Title</b> - Description of the <a href="https://github.com/emberry-org/emberry">Project</a> !<br>
</div>

<br>

<div align="center">
    <a href="#inverse-kinematics-impl">Inverse Kinematics</a>
    ·
    <a href="#matrix-affine-transformations-impl">Matrix Affine Transformations</a>
</div>
    
<br>

<h2>Inverse Kinematics <sub><i>impl</i></sub></h2>
<a href="https://github.com/mxcop/buas-intake/blob/main/src/physics/bone.cpp"><code>~src/physics/bone.cpp</code></a><br><br>

I implemented inverse kinematics by researching multiple existing implementations *(usually written in other languages)*<br>
My current implementation uses recursion to simulate the bones, this is not the most optimal way of doing this.<br>
Nevertheless this was the easiest way to implement it.

Below you can see the resursive update function called on each bone in the sequence.<br>
It simply rotates towards the start position of the next bone in the sequence using a little bit of math.

```cpp
/// Recursively update the rotation of each bone.
float2 Bone::Update(float2 target)
{
    // Convert from parent to local coordinate space.
    float2 local = (target - offset).rotate(-angle);

    // Recursively loop until we have the start position of the next bone.
    float2 next;
    if (child != nullptr) next = child->Update(local);
    // Default next start position for the last bone in the sequence.
    else next = float2(len, 0);
        
    // Point towards the start position of the next bone.
    float deltaAngle = atan2(local.y, local.x) - atan2(next.y, next.x);
    angle += deltaAngle;

    // Convert back to parent coordinate space.
    return offset + next.rotate(angle);
}
```

Then to draw the sequence to the screen I just recursively draw each bone in the sequence.<br>
This function can look a bit overwhelming due to having to pass through the previous end position ``(float2 p)``<br>
And a sum of all previous angles ``(float w_angle)``.

```cpp
/// Recursively draw each bone.
void Bone::Draw(Tmpl8::Surface* screen, float2 p, float w_angle, bool origin)
{
    w_angle += angle;

    if (origin) {
        screen->Line(offset.x + p.x, offset.y + p.y, offset.x + p.x + cos(w_angle) * len, offset.y + p.y + sin(w_angle) * len, 0xffffff);
        if (child != nullptr) child->Draw(screen, float2(offset.x + p.x + cos(w_angle) * len, offset.y + p.y + sin(w_angle) * len), w_angle);
    }
    else {
        screen->Line(p.x, p.y, p.x + cos(w_angle) * len, p.y + sin(w_angle) * len, 0xffffff);
        if (child != nullptr) child->Draw(screen, float2(p.x + cos(w_angle) * len, p.y + sin(w_angle) * len), w_angle);
    }
}
```

<br>

<h2>Matrix Affine Transformations <sub><i>impl</i></sub></h2>
<a href="https://github.com/mxcop/buas-intake/blob/main/src/utils/math/mat3x3.cpp"><code>~src/utils/math/mat3x3.cpp</code></a><br>
<a href="https://github.com/mxcop/buas-intake/blob/main/src/engine/surface.cpp"><code>~src/engine/surface.cpp</code></a><br><br>

I updated the engine template to be able to draw sprites using matrices.<br>
Using my own matrix class implementation ``(mat3x3)``

First I invert the transformation matrix because I'm going to use it to turn screen positions into texture positions.<br>
Then I figure out the bounding box of the transformed sprite I'm about to draw.<br>
<sub><i>This is important because I need to itterate over each pixel contained by the transformed sprite to be able to draw them.</i></sub>

```cpp
// Get the inverted matrix.
mat3x3 inverted = matrix.inverted();

// Get the minX, minY and maxX, maxY of the transformed sprite:
float2 min;
float2 max;
matrix.bounds(m_Width, m_Height, min, max);
```

Next I loop over all pixels within the bounding box and convert these screen positions into texture positions.<br>
Then I sample these pixels and draw them onto the target buffer.

```cpp
// Loop through each pixel within the transformed bounding box:
for (size_t x = min.x; x < max.x; x++)
{
  // Check if this X axis is onscreen.
  if (x < 0 || x >= target_w) continue;

  for (size_t y = min.y; y < max.y; y++)
  {
    // Check if this Y axis is onscreen.
    if (y < 0 || y >= target_h) continue;

    // Convert the screen position into texture space.
    float2 pixel_pos = inverted.transform(float2(x, y)) + float2(0.5, 0.5);

    // Check if the pixel position is within bounds of the texture. (for rotations)
    if (pixel_pos.x < 0 || pixel_pos.y < 0 || pixel_pos.x >= m_Width || pixel_pos.y >= m_Height) continue;

    // Sample the texture.
    const Pixel pixel = *(src + static_cast<int>(pixel_pos.y) * m_Width + static_cast<int>(pixel_pos.x));
  
    if (m_Flags & FLARE) // Alpha blending :
    {
      // Get the pixel in the position we're writing too.
      const Pixel active_pixel = *(des + y * target_w + x);

      // Blend the two pixels together.
      *(des + y * target_w + x) = AddBlend(pixel, active_pixel);
    }
    else *(des + y * target_w + x) = pixel;
  }
}
```
