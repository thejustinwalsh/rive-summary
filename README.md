# Rive Summary

Generate a summary of the Artboards, Animations, and Object count from a [Rive](https://rive.app/) file.

> Usage: rive-summary path-to-file.riv

### Installation
1. Clone the repository and initialize the submodules
```bash
git clone --recurse-submodules https://github.com/thejustinwalsh/rive-summary
```

2. Initialize
```bash
cd rive-summary
./dev/init.sh
```

3. Compile
```bash
./dev/build.sh
```

4. Run
```bash
./build/bin/debug/main ./assets/off_road_car_blog_0_6.riv
```

5. Hack
```bash
code .
```

### VS Code

 The `.vscode` directory contains some sane defaults to get you up and running quickly.

#### Tasks
 - Build Debug
 - Build Release
 - Initialize Project

 #### Debugging
 - Debugging is already configured in the launch.json as well.