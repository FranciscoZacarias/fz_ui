
## Renderer

### CRITICAL - Implement First

- [x] Text rendering screenspace - Render text in screen coordinates for UI and debug info
- [x] Screenspace texture rendering - Render texture in 2D screenspace
- [x] Create fallback texture - Default texture when loading fails to prevent crashes
- [x] Wireframe mode toggle - Switch between filled and wireframe rendering for debugging
- [x] Add triangle render primitives

### CORE FEATURES - High Priority

- [x] 2D primitives should be able to just set colors without making new textures
- [x] Add normals to render primitives
- [ ] Directional light pass
- [ ] Implement depth sorting for transparency - Sort transparent objects back-to-front for correct alpha blending
- [ ] Draw screenspace circles - Render circles in screen coordinates for UI
- [ ] Thicker lines - Variable width lines instead of 1-pixel GL_LINES
- [ ] Screenspace quads rounded edges - UI quads with configurable corner radius

### UI/UX FEATURES - Medium Priority

- [ ] Border - Add border customization to primitives like thickness and color
- [ ] Round corners - Add round corners to quads
- [ ] Gradient fills - Linear and radial gradients for primitives rendering
- [ ] Scissor/clipping rectangles - Clip rendering to specific screen regions
- [ ] Render stats display - Show performance metrics like draw calls and instance counts

### DEBUG/UTILITY - Medium Priority

- [x] Screenspace line rendering
- [x] Draw normals on primitives
- [x] Grid rendering - Draw world-space grid lines for spatial reference
- [x] Bounding box visualization - Render wireframe boxes around objects for debugging

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