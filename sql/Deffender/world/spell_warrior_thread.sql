-- ----------
-- Tank Class Passive Threat
-- ----------
DELETE FROM spell_linked_spell WHERE spell_effect = 57339;
INSERT INTO spell_linked_spell VALUES
(7376,  57339, 2, 'Defensive Stance Passive - Tank Class Passive Threat');

DELETE FROM spell_threat WHERE entry IN (
845,
7369,
11608,
11609,
20569,
25231,
47519,
47520,
78,
284,
285,
1608,
11564,
11565,
11566,
11567,
25286,
29707,
30324,
47449,
47450,
57755,
6572,
6574,
7379,
11600,
11601,
25288,
25269,
30357,
57823,
23922,
23923,
23924,
23925,
25258,
30356,
47487,
47488,
1464,
8820,
11604,
11605,
25241,
25242,
47474,
47475,
7386,
20243,
6343,
25212,
12799,
29704,
11879,
47440,
47437,
1715,
47467,
30016,
30022,
47497,
47498,
47502,
47501
);
INSERT INTO `spell_threat` VALUES
    (12799, 25,  1.00, 0.0),  -- Improved Revenge (Rank 2)
    (29704, 36,  1.00, 0.0),  -- Shield Bash
    (11879, 104, 1.00, 0.0),  -- Disarm
    (47440, 80,  1.00, 0.0),  -- Commanding Shout
    (47437, 63,  1.00, 0.0),  -- Demoralizing Shout (Rank 8)
    (1715, 181,  1.00, 0.0),  -- Harmstring (Rank 4)
    (845,   15,   1.00, 0.0), -- Cleave (Rank 1)
    (7369,  25,  1.00, 0.0),  -- Cleave (Rank 2)
    (11608, 35,  1.00, 0.0),  -- Cleave (Rank 3)
    (11609, 48,  1.00, 0.0),  -- Cleave (Rank 4)
    (20569, 69,  1.00, 0.0),  -- Cleave (Rank 5)
    (25231, 95,  1.00, 0.0),  -- Cleave (Rank 6)
    (47519, 112, 1.00, 0.0),  -- Cleave (Rank 7)
    (47520, 225, 1.00, 0.0),  -- Cleave (Rank 8)
    (78,    5,   1.00, 0.0),  -- Heroic Strike (Rank 1)
    (284,   10,  1.00, 0.0),  -- Heroic Strike (Rank 2)
    (285,   16,  1.00, 0.0),  -- Heroic Strike (Rank 3)
    (1608,  22,  1.00, 0.0),  -- Heroic Strike (Rank 4)
    (11564, 31,  1.00, 0.0),  -- Heroic Strike (Rank 5)
    (11565, 48,  1.00, 0.0),  -- Heroic Strike (Rank 6)
    (11566, 70,  1.00, 0.0),  -- Heroic Strike (Rank 7)
    (11567, 92,  1.00, 0.0),  -- Heroic Strike (Rank 8)
    (25286, 104, 1.00, 0.0),  -- Heroic Strike (Rank 9)
    (29707, 121, 1.00, 0.0),  -- Heroic Strike (Rank 10)
    (30324, 164, 1.00, 0.0),  -- Heroic Strike (Rank 11)
    (47449, 224, 1.00, 0.0),  -- Heroic Strike (Rank 12)
    (47450, 259, 1.00, 0.0),  -- Heroic Strike (Rank 13)
    (57755, 0,   1.50, 0.0),  -- Heroic Throw
    (6572,  7,   1.00, 0.0),  -- Revenge (Rank 1)
    (6574,  11,  1.00, 0.0),  -- Revenge (Rank 2)
    (7379,  15,  1.00, 0.0),  -- Revenge (Rank 3)
    (11600, 27,  1.00, 0.0),  -- Revenge (Rank 4)
    (11601, 41,  1.00, 0.0),  -- Revenge (Rank 5)
    (25288, 53,  1.00, 0.0),  -- Revenge (Rank 6)
    (25269, 58,  1.00, 0.0),  -- Revenge (Rank 7)
    (30357, 71,  1.00, 0.0),  -- Revenge (Rank 8)
    (57823, 121, 1.00, 0.0),  -- Revenge (Rank 9)
    (23922, 228, 1.00, 0.0),  -- Shield Slam (Rank 1)
    (23923, 268, 1.00, 0.0),  -- Shield Slam (Rank 2)
    (23924, 307, 1.00, 0.0),  -- Shield Slam (Rank 3)
    (23925, 347, 1.00, 0.0),  -- Shield Slam (Rank 4)
    (25258, 387, 1.00, 0.0),  -- Shield Slam (Rank 5)
    (30356, 426, 1.00, 0.0),  -- Shield Slam (Rank 6)
    (47487, 650, 1.00, 0.0),  -- Shield Slam (Rank 7)
    (47488, 770, 1.00, 0.0),  -- Shield Slam (Rank 8)
    (1464,  18,  1.00, 0.0),  -- Slam (Rank 1)
    (8820,  24,  1.00, 0.0),  -- Slam (Rank 2)
    (11604, 38,  1.00, 0.0),  -- Slam (Rank 3)
    (11605, 49,  1.00, 0.0),  -- Slam (Rank 4)
    (25241, 59,  1.00, 0.0),  -- Slam (Rank 5)
    (25242, 78,  1.00, 0.0),  -- Slam (Rank 6)
    (47474, 123, 1.00, 0.0),  -- Slam (Rank 7)
    (47475, 140, 1.00, 0.0),  -- Slam (Rank 8)
    (47467, 345, 1.00, 0.05), -- Sunder Armor (Rank 7)
    (20243, 0,   1.00, 0.05), -- Devastate (Rank 1)
    (30016, 0,   1.00, 0.05), -- Devastate (Rank 2)
    (30022, 0,   1.00, 0.05), -- Devastate (Rank 3)
    (47497, 0,   1.00, 0.05), -- Devastate (Rank 4)
    (47498, 0,   1.00, 0.05), -- Devastate (Rank 5)
    (47502, 0,   1.85, 0.0),  -- Thunder Clap (Rank 9)
    (47501, 0,   1.85, 0.0),  -- Thunder Clap (Rank 8)
    (6343,  0,   1.85, 0.0);  -- Thunder Clap (Rank 1)