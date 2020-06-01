using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AsteroidSpawner : MonoBehaviour
{
    [SerializeField]
    GameObject asterPrefab = null;
    /// <summary>
    /// Spawner of random-directed asteroids
    /// </summary>
    // Start is called before the first frame update
    void Start()
    {
        
        GameObject asteroid = Instantiate(asterPrefab);
        float coll_radius = asteroid.GetComponent<CircleCollider2D>().radius;
        asteroid.GetComponent<Asteroid>().Initialize(Direction.Down, new Vector3(0, ScreenUtils.ScreenTop + coll_radius, 0));
        asteroid = Instantiate(asterPrefab);
        asteroid.GetComponent<Asteroid>().Initialize(Direction.Up, new Vector3(0, ScreenUtils.ScreenBottom - coll_radius, 0));
        asteroid = Instantiate(asterPrefab);
        asteroid.GetComponent<Asteroid>().Initialize(Direction.Left, new Vector3(ScreenUtils.ScreenRight + coll_radius, 0, 0));
        asteroid = Instantiate(asterPrefab);
        asteroid.GetComponent<Asteroid>().Initialize(Direction.Right, new Vector3(ScreenUtils.ScreenLeft - coll_radius, 0, 0));
    }
}
