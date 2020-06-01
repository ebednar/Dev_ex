using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Script for bullet's moving
/// </summary>
public class Bullet : MonoBehaviour
{
    const float life_time = 2.0f;
    Timer timer;

    private void Start()
    {
        timer = gameObject.AddComponent<Timer>();
        timer.Duration = life_time;
        timer.Run();
    }

    private void Update()
    {
        if (timer.Finished)
            Destroy(gameObject);
    }
    /// <summary>
    /// Apply force to bullet in current direction
    /// </summary>
    /// <param name="dir"></param>
    public void ApplyForce(Vector2 dir)
    {
        const float force = 4.5f;
        GetComponent<Rigidbody2D>().AddForce(force * dir, ForceMode2D.Impulse);
    }
}
    