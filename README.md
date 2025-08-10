
## Renderer

### CRITICAL - Implement First

- [x] Text rendering screenspace - Render text in screen coordinates for UI and debug info
- [x] Text rendering worldspace - Render text positioned in 3D world space
- [x] Screenspace texture rendering - Render texture in 2D screenspace
- [x] Create fallback texture - Default texture when loading fails to prevent crashes
- [x] Wireframe mode toggle - Switch between filled and wireframe rendering for debugging
- [x] Change worldspace quads such that I can transform them - Add rotation support to quad instances
- [x] Add triangle render primitives

### CORE FEATURES - High Priority

- [x] Add normals to render primitives
- [ ] Directional light pass
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

- [x] Screenspace line rendering
- [x] Draw normals on primitives
- [x] Grid rendering - Draw world-space grid lines for spatial reference
- [x] Bounding box visualization - Render wireframe boxes around objects for debugging
- [x] Draw arrow worldspace - 3D arrows with proper arrowhead geometry

### ADVANCED RENDERING - Lower Priority

- [ ] Multiple render targets/framebuffers - Support for off-screen rendering and post-processing
- [ ] MSAA support - Multi-sample anti-aliasing for smoother edges
- [ ] Shadow mapping - Basic directional light shadow casting
- [ ] Bloom/glow effect - Post-processing effect for bright light sources
- [ ] Particle system - GPU-based particle rendering with instancing

### PERFORMANCE - When needed

- [ ] Frustum culling - Skip rendering objects outside camera view
- [ ] Texture atlasing system - Combine multiple textures to reduce binding overhead
- [ ] GPU Timer queries - Measure GPU performance for bottleneck identification

### BUGS 

- [ ] Camera is janky, especially when pressing like 2, 3 or more keys at once
- [x] Screenspace text rendering appears on a base line, is scaled by pixel height and position from the quad center
- [ ] Worldspace  text rendering appears on a base line, is scaled by pixel height and position from the quad center

## Game

## fz_std

- [ ] Window and Input should not be globals, they should be returned to userspace on initialization.
- [ ] Put all functions definitions together and structs at the top 
- [ ] Implement os_message_box
- [ ] Add os_message_box to failed asserts and emit_fatal