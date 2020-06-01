using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScreenWraper : MonoBehaviour
{
    float ColRadius; // radius of collider
    // Start is called before the first frame update
    void Start()
    {
        ColRadius = gameObject.GetComponent<CircleCollider2D>().radius;
    }

    // when object go beyond screen 
    void OnBecameInvisible()
    {
        Vector2 pos = gameObject.transform.position;
        if (pos.x + ColRadius > ScreenUtils.ScreenRight) // right edge
            pos.x = ScreenUtils.ScreenLeft - ColRadius;
        else if (pos.x - ColRadius < ScreenUtils.ScreenLeft) // left edge
            pos.x = ScreenUtils.ScreenRight + ColRadius;
        if (pos.y + ColRadius > ScreenUtils.ScreenTop) // top edge
            pos.y = ScreenUtils.ScreenBottom - ColRadius;
        else if (pos.y - ColRadius < ScreenUtils.ScreenBottom) // bottom edge
            pos.y = ScreenUtils.ScreenTop + ColRadius;
        gameObject.transform.position = pos;
    }
}
