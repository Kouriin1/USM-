import os
import keyboard
import pygame
import numpy as np

maps = {
    "level1": [
        ["#", "#", "#", "#", "#", "#", "#"],
        ["#", ".", ".", ".", "f", ".", "#"],
        ["#", "#", "#", ".", "#", ".", "#"],
        ["#", "x", ".", ".", "#", "f", "#"],
        ["#", ".", "#", ".", ".", ".", "#"],
        ["#", "g", "#", "x", "#", "f", "#"],
        ["#", "#", "#", "#", "#", "#", "#"]
    ],
    "level2": [
        ["#", "#", "#", "#", "#", "#", "#"],
        ["#", ".", "#", ".", "f", ".", "#"],
        ["#", ".", "#", ".", "#", ".", "#"],
        ["#", ".", ".", ".", "#", "x", "#"],
        ["#", "#", "#", ".", "#", "f", "#"],
        ["#", "g", ".", ".", "x", "f", "#"],
        ["#", "#", "#", "#", "#", "#", "#"]
    ],
    "level3": [
        ["#", "#", "#", "#", "#", "#", "#"],
        ["#", ".", "b", ".", "f", ".", "#"],
        ["#", "#", ".", ".", "#", ".", "#"],
        ["#", "x", ".", "#", "#", "f", "#"],
        ["#", "g", "#", ".", ".", ".", "#"],
        ["#", ".", "#", "x", "#", "f", "#"],
        ["#", "#", "#", "#", "#", "#", "#"]
    ]
}


avatar_y = 2
avatar_x = 2
counting_fruits = 0
counting_x = 0
limit = 20
level = ["level1", "level2", "level3"]
pase = 0

# Inicializar pygame mixer para música y sonidos
pygame.mixer.init()

# Funciones para crear sonidos simples
def make_sound(freq=440, duration=0.2, volume=0.5):
    sample_rate = 44100
    t = np.linspace(0, duration, int(sample_rate * duration), False)
    wave = 0.5 * np.sin(2 * np.pi * freq * t)
    sound_array = (wave * 32767).astype(np.int16)
    sound_array_stereo = np.column_stack((sound_array, sound_array))
    sound = pygame.sndarray.make_sound(sound_array_stereo)
    sound.set_volume(volume)
    return sound

# Música de fondo (acorde simple)
def background_music():
    sample_rate = 44100
    duration = 0.5
    frecuencias = [261.63, 329.63, 392.00, 523.25]  # C4, E4, G4, C5
    musica = []
    for freq in frecuencias:
        t = np.linspace(0, duration, int(sample_rate * duration), False)
        wave = 0.2 * np.sin(2 * np.pi * freq * t)
        sound_array = (wave * 32767).astype(np.int16)
        musica.append(sound_array)
    musica_array = np.concatenate(musica)
    musica_array_stereo = np.column_stack((musica_array, musica_array))
    sound = pygame.sndarray.make_sound(musica_array_stereo)
    sound.set_volume(0.2)
    return sound

# Efectos de sonido
sound_fruit = make_sound(880, 0.15, 0.6)
sound_x = make_sound(220, 0.15, 0.6)
sound_gift = make_sound(1200, 0.25, 0.7)
sound_bomb = make_sound(80, 0.4, 0.7)
bg_music = background_music()
bg_music.play(loops=-1)

# Música de victoria y derrota
def victory_music():
    sample_rate = 44100
    duration = 0.3
    notes = [523.25, 659.25, 783.99, 1046.50]  # C5, E5, G5, C6
    music = []
    for freq in notes:
        t = np.linspace(0, duration, int(sample_rate * duration), False)
        wave = 0.4 * np.sin(2 * np.pi * freq * t)
        sound_array = (wave * 32767).astype(np.int16)
        music.append(sound_array)
    music_array = np.concatenate(music)
    music_array_stereo = np.column_stack((music_array, music_array))
    sound = pygame.sndarray.make_sound(music_array_stereo)
    sound.set_volume(0.7)
    return sound

def defeat_music():
    sample_rate = 44100
    duration = 0.4
    notes = [196.00, 174.61, 164.81, 130.81]  # G3, F3, E3, C3
    music = []
    for freq in notes:
        t = np.linspace(0, duration, int(sample_rate * duration), False)
        wave = 0.4 * np.sin(2 * np.pi * freq * t)
        sound_array = (wave * 32767).astype(np.int16)
        music.append(sound_array)
    music_array = np.concatenate(music)
    music_array_stereo = np.column_stack((music_array, music_array))
    sound = pygame.sndarray.make_sound(music_array_stereo)
    sound.set_volume(0.7)
    return sound

sound_victory = victory_music()
sound_defeat = defeat_music()

def fn_clear_map():
    os.system("cls" if os.name == "nt" else "clear")

def fn_render_map():
    
    fn_clear_map()
    for rows in maps[level[pase]]:
        tiles = []
        for cols in rows:
            if cols == ".":
                tiles.append("⬜")
            if cols == "#":
                tiles.append("🧱")
            if cols == "@":
                tiles.append("😃")
            if cols == "f":
                tiles.append("🍒")
            if cols == "g":
                tiles.append("🎁")
            if cols == "x":
                tiles.append("❌")
            if cols == "b":
                tiles.append("💣")
        print(" ".join(tiles))
    print(f"Frutas recogidas: {counting_fruits}")
    print(f"X recogidas: {counting_x}")
    print("limite de movimientos: ", limit)


def fn_move_avatar():
    global avatar_x, avatar_y, counting_fruits, counting_x, pase, limit
    new_x = avatar_x
    new_y = avatar_y

    while True:
        event = keyboard.read_event(suppress=True)
        if event.event_type == keyboard.KEY_DOWN:
            if event.name == "w":
                new_y -= 1
                limit -= 1           
            elif event.name == "s":
                new_y += 1
                limit -= 1
            elif event.name == "a":
                new_x -= 1
                limit -= 1
            elif event.name == "d":
                new_x += 1
                limit -= 1
            elif event.name == "q":
                print("Juego terminado")
                exit()
            if limit == 0:
                print("Chao agubueniao")
                bg_music.stop()
                sound_defeat.play()
                pygame.time.wait(1800)
                exit()
            
            current_map = maps[level[pase]]
            if (0 <= new_x < len(current_map) and 0 <= new_y < len(current_map) and current_map[new_y][new_x] != "#"):
                current_map[avatar_y][avatar_x] = "."
                avatar_x = new_x
                avatar_y = new_y
                if current_map[avatar_y][avatar_x] == "f":
                    counting_fruits += 1
                    sound_fruit.play()

                if current_map[avatar_y][avatar_x] == "x":
                    counting_x += 1
                    sound_x.play()

                if current_map[avatar_y][avatar_x] == "g":
                    print("Has encontrado el regalo 🎁")
                    print("4 intentos adicionales se suman")
                    limit += 4
                    sound_gift.play()
                    os.system("pause")
                if current_map[avatar_y][avatar_x] == "b":
                    print("Has pisado una bomba 💣")
                    print("Juego terminado")
                    sound_bomb.play()
                    bg_music.stop()
                    sound_defeat.play()
                    pygame.time.wait(1800)
                    exit()
                    

                if counting_fruits == 3 and counting_x == 2:
                    print("Nivel completado, pasando al siguiente nivel")
                    counting_fruits = 0
                    counting_x = 0
                    pase += 1
                    avatar_x = 2
                    avatar_y = 2
                    if pase == 1:
                        limit = 15
                    elif pase == 2:
                        limit = 16
                    elif pase == 3:
                        print("GANASTE EL JUEGO")
                        bg_music.stop()
                        sound_victory.play()
                        pygame.time.wait(1800)
                        exit()
                    os.system("pause")
                    fn_render_map()
                    fn_move_avatar()
                    break
                
                current_map[avatar_y][avatar_x] = "@"
            else:
                new_x = avatar_x
                new_y = avatar_y
            fn_render_map()
            fn_move_avatar()

def game():
    global pase, limit
    pase = 0
    limit = 20
    fn_render_map()
    fn_move_avatar()

def menu():

    while True:
        os.system("cls" if os.name == "nt" else "clear")
        print("""
        |-----------------------------------------|
        |-------------Laberinto Game--------------|
        |-----------------------------------------|
        |1) Jugar                                 |
        |2) Salir                                 |
        |                                         |
        |-----------------------------------------|
        """.center(90," "))
        op = int(input("opcion: "))
        if op == 1:
           game()
        elif op == 2:
            exit()
        else: 
            break
        



if __name__ == "__main__":
    menu()
    