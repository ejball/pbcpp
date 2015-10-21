import os.path

top = '.'
out = 'build'

def options(ctx):
    ctx.load('pebble_sdk')

def configure(ctx):
    ctx.load('pebble_sdk')

    ctx.load('g++')
    for p in ctx.env.TARGET_PLATFORMS:
        env = ctx.all_envs[p]
        for k in ctx.env.keys():
            if not env[k]:
                env[k] = ctx.env[k]
        env.CXX = 'arm-none-eabi-g++'
        env.CXXFLAGS = list(env.CFLAGS)
        env.CXXFLAGS.remove('-std=c99')
        env.CXXFLAGS.extend(['-std=gnu++11', '-fPIE', '-fno-unwind-tables', '-fno-exceptions', '-Wl,--stack,200', '-fno-threadsafe-statics', '-fno-rtti'])

def build(ctx):
    ctx.load('pebble_sdk')

    build_worker = os.path.exists('worker_src')
    binaries = []

    for p in ctx.env.TARGET_PLATFORMS:
        ctx.set_env(ctx.all_envs[p])
        ctx.set_group(ctx.env.PLATFORM_NAME)
        app_elf='{}/pebble-app.elf'.format(ctx.env.BUILD_DIR)
        ctx.pbl_program(source=ctx.path.ant_glob('src/**/*.cpp'),
        target=app_elf)

        if build_worker:
            worker_elf='{}/pebble-worker.elf'.format(ctx.env.BUILD_DIR)
            binaries.append({'platform': p, 'app_elf': app_elf, 'worker_elf': worker_elf})
            ctx.pbl_worker(source=ctx.path.ant_glob('worker_src/**/*.cpp'),
            target=worker_elf)
        else:
            binaries.append({'platform': p, 'app_elf': app_elf})

    ctx.set_group('bundle')
    ctx.pbl_bundle(binaries=binaries, js=ctx.path.ant_glob('src/js/**/*.js'))
