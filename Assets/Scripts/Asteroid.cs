using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// script for Asteroid object
/// </summary>
public class Asteroid : MonoBehaviour
{
    [SerializeField]
    Sprite[] Asters = new Sprite[3];

    // Start is called before the first frame update
    void Start()
    {
        // choose random sprite
        int rand = Random.Range(0, 3);
        SpriteRenderer spriteRenderer = GetComponent<SpriteRenderer>();
        spriteRenderer.sprite = Asters[rand];
        
    }

    public void Initialize(Direction dir, Vector3 position)
    {
        // start position
        transform.position = position;
        // start impulse
        const float MinImpulseForce = 2f;
        const float MaxImpulseForce = 2.6f;
        float angle = (Random.Range(- 20, 20) + 90 * (int)dir) * Mathf.Deg2Rad;
        Vector2 move_direction = new Vector2(Mathf.Cos(angle), Mathf.Sin(angle));
        float magnitude = Random.Range(MinImpulseForce, MaxImpulseForce);
        GetComponent<Rigidbody2D>().AddForce(move_direction * magnitude, ForceMode2D.Impulse);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Bullet")
            Destroy(gameObject);
    }
}
