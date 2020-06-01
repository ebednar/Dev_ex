using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/// <summary>
/// script for ship control
/// </summary>

public class Ship : MonoBehaviour
{
    [SerializeField]
    GameObject prefabBullet;
    Rigidbody2D shipRb;
    Vector2 thrustDirection = new Vector2(1.0f, 0.0f);
    const int ThrustForce = 100;
    bool isThrust = false;
    const int RotateDegreesPerSecond = 100;
    // Start is called before the first frame update
    void Start()
    {
        shipRb = gameObject.GetComponent<Rigidbody2D>();
    }

    // physic's update for thrust
    void FixedUpdate()
    {
        // move ship forward on space
        if (Input.GetAxis("Thrust") > 0)
        {
            if (!isThrust) // to detect one press
            {
                isThrust = true;
                shipRb.velocity = Vector2.zero; // nullify previous force
                shipRb.angularVelocity = 0.0f; // nullify previous force
                shipRb.AddForce(ThrustForce * thrustDirection);
            }
        }
        else
            isThrust = false;

        //rotate ship by left and right arrows
        float rotationInput = Input.GetAxis("Rotate");
        if (rotationInput != 0)
        {
            float rotationAmount = rotationInput * RotateDegreesPerSecond * Time.fixedDeltaTime;
            transform.Rotate(Vector3.forward, rotationAmount); // rotate ship

            // rotate thrust direction
            thrustDirection.x = Mathf.Cos(Mathf.Deg2Rad * transform.eulerAngles.z);
            thrustDirection.y = Mathf.Sin(Mathf.Deg2Rad * transform.eulerAngles.z);
        }
    }

    private void Update()
    {
        GameObject bullet;
        if (Input.GetKeyDown(KeyCode.LeftControl) || Input.GetKeyDown(KeyCode.LeftCommand))
        {
            bullet = Instantiate(prefabBullet);
            bullet.transform.position = transform.position;
            bullet.transform.rotation = transform.rotation;
            bullet.GetComponent<Bullet>().ApplyForce(thrustDirection);
        }
    }
    /// <summary>
    /// Destructoin on collision with asteroid
    /// </summary>
    /// <param name="collision"></param>
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Asteroid")
            Destroy(gameObject);
    }
}
