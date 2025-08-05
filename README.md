
## Renderer

### CRITICAL - Implement First

- [x] Text rendering screenspace - Render text in screen coordinates for UI and debug info
- [ ] Text rendering worldspace - Render text positioned in 3D world space
- [ ] Screenspace texture rendering - Render texture in 2D screenspace
- [ ] Create fallback texture - Default texture when loading fails to prevent crashes
- [ ] Wireframe mode toggle - Switch between filled and wireframe rendering for debugging
- [ ] Change worldspace quads such that I can transform them - Add rotation support to quad instances

### CORE FEATURES - High Priority

- [ ] Implement depth sorting for transparency - Sort transparent objects back-to-front for correct alpha blending
- [ ] Draw worldspace circles - Render circles positioned in 3D space
- [ ] Draw screenspace circles - Render circles in screen coordinates for UI
- [ ] Draw worldspace spheres - 3D sphere rendering with proper shading
- [ ] Draw box worldspace - Wireframe or filled box rendering in 3D space
- [ ] Thicker lines - Variable width lines instead of 1-pixel GL_LINES
- [ ] Screenspace quads rounded edges - UI quads with configurable corner radius

### UI/UX FEATURES - Medium Priority

- [ ] Gradient fills - Linear and radial gradients for quad rendering
- [ ] Scissor/clipping rectangles - Clip rendering to specific screen regions
- [ ] Render stats display - Show performance metrics like draw calls and instance counts

### DEBUG/UTILITY - Medium Priority

- [ ] Grid rendering - Draw world-space grid lines for spatial reference
- [ ] Bounding box visualization - Render wireframe boxes around objects for debugging
- [ ] Draw arrow worldspace - 3D arrows with proper arrowhead geometry

### ADVANCED RENDERING - Lower Priority

- [ ] Multiple render targets/framebuffers - Support for off-screen rendering and post-processing
- [ ] MSAA support - Multi-sample anti-aliasing for smoother edges
- [ ] Shadow mapping - Basic directional light shadow casting
- [ ] Bloom/glow effect - Post-processing effect for bright light sources
- [ ] Particle system - GPU-based particle rendering with instancing

### PERFORMANCE - Implement When Needed

- [ ] Frustum culling - Skip rendering objects outside camera view
- [ ] Texture atlasing system - Combine multiple textures to reduce binding overhead
- [ ] GPU Timer queries - Measure GPU performance for bottleneck identification