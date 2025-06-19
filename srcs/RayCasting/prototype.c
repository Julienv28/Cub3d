#include <stdio.h>
#include <math.h>

// #define MAP_WIDTH 8
// #define MAP_HEIGHT 8
// #define NUM_RAYS 60
// #define FOV (M_PI / 3) // 60 degrés

// Carte de test (1 = mur, 0 = vide)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

// Position du joueur
float playerX = 3.5f;
float playerY = 3.5f;
float playerAngle = M_PI / 2; // angle en radians (vers le haut)

// Prototype à implémenter
float cast_ray(float rayAngle, float px, float py, int map[MAP_HEIGHT][MAP_WIDTH]) {
    // Direction du rayon (vecteur unitaire)
    float dx = cosf(rayAngle);
    float dy = sinf(rayAngle);

    // Position courante du rayon (en float)
    float rayX = px;
    float rayY = py;

    // Pas de déplacement
    float stepSize = 0.05f; // plus petit = plus précis
    float distance = 0.0f;

    while (distance < 20.0f) { // on limite la distance max à 20 cases
        rayX += dx * stepSize;
        rayY += dy * stepSize;
        distance += stepSize;

        int mapX = (int)rayX;
        int mapY = (int)rayY;

        // Vérifie qu'on ne sort pas de la map
        if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
            return FLT_MAX; // infini : pas de mur trouvé dans la map

        // Collision avec un mur
        if (map[mapY][mapX] == 1)
            return distance;
    }

    return FLT_MAX; // rien trouvé
}

int main(void) {
    printf("Ray Casting Test:\n");
    for (int i = 0; i < NUM_RAYS; ++i) {
        float rayAngle = playerAngle - (FOV / 2) + (FOV / NUM_RAYS) * i;
        float distance = cast_ray(rayAngle, playerX, playerY, map);
        printf("Ray %2d | Angle: %.2f | Distance: %.2f\n", i, rayAngle, distance);
    }
    return 0;
}

