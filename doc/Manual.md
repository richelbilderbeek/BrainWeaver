# Brainweaver manual

Brainweaver is a tool used by teachers that teach students to become
a teacher. 

It is beneficial for students to force these to think about
their own working theory. One of the ways to do so, is to
let the student create a concept map.

In Brainweaver,

 * a teacher ('Assessor') creates a file with a focal question
 * the student creates a concept map around that focal question
 * the teacher grades the concept map made by the students

## Controls

### General controls

 * `CTRL + S`: save

### Edit a concept map

#### Mouse

 * Double-click: create a new concept

#### Keyboard

 * `CTRL + N`: create a new concept
 * `CTRL + E`: create a relation between two selected concepts
 * Space: select a random concept or relation
 * `SHIFT + arrows`: add concepts to selection
 * `CTRL + arrows`: move selected concepts
 * `CTRL + Z`: undo
 * `CTRL + SHIFT + Z`: redo
 * `CTRL + H`: toggle arrow head, when having selected a relation
 * `CTRL + T`: toggle arrow tail, when having selected a relation
 * `ESC`: cancel creating a new relation, or close the dialog
 * F2: edit the concept or relation


## Recovering files

Every couple of seconds, the concept map is saved. 
Would Brainweaver be interrupted roughly (for example,
the computer its power cord is pulled), that concept map
can still be recovered. 

Just load the file `autosave1.cmp`. 

## What is the file `autosave1.cmp`?

An auto-saved file.

Brainweaver saves a concept map every 1-10 seconds
as `autosave1.cmp` and `autosave2.cmp`

## What is the file `autosave2.cmp`?

An auto-saved file, that may be corrupt.

When Brainweaver saves a concept map every couple of seconds,
it first creates `autosave2.cmp`. If this fails, and `autosave2.cmp`
becomes corrupted, `autosave1.cmp` is still valid.

If `autosave2.cmp` can be created, it is assumed that `autosave1.cmp`
can be created with the same lack of errors.

## Calculations


### Complexity (estimated, that is, using the graph information only)

 * `n_n`: Number of nodes, excluding the focal question node
 * `n_r`: Number of relations, excluding the relations connected to the focal question node
 * `x`: complexity (estimated): `100.0 * (((n_r * 2) / (n_n * (n_n - 1))) ^ 0.25)`


Assumes `n_n` at least being `2`.

`n`|1|2|3|4|5|6
---|---|---|---|---|---|---
`n_n`|`  2`|`  2`|`  3`|`  3`|`  3`|`  3`
`n_r`|`  0`|`  1`|`  0`|`  1`|`  2`|`  3`
---|---|---|---|---|---|---
`x  `|`  0`|`100`|`  0`|` 76`|` 90`|`100`


### Complexity (experimental, that is, working on input from humans)

 * `k_i`: sum of all nodes' complexity, as rated by a human, excluding the focal question node
 * `n_n`: number of all nodes , excluding the focal question node
 * `x`: complexity: `x = 50 * k_i / n_n`


### Richness (experimental, that is, working on input from humans)

Richness is calculated as the equation below (from [1], page 617):

![Richness](Richness.png)

where

 * `a`: the number of domains of knowledge, excluding 'misc'
 * `b`: the number of domains (excluding 'misc') with a relative frequency between 12% and 25%

In Brainweaver, there are seven domains, of which 'misc' is excluded from the calculation:

 * `profession`: 'Beroepsdomein'
 * `organisations`: 'Organisaties'
 * `social_surroundings`: 'Sociale omgeving'
 * `target_audience`: 'Doelgroep'
 * `ti_knowledge`: 'Technical Instrumental knowledge', NL: 'Technische instrumentele kennis'
 * `prof_growth`: Professionele groei
 * `misc`: 'Overig'

To demonstrate this calculation, we will use a concept map with
only one added node with some examples:

`Competency         `|`#`|`  #`|`  #`|`  #`
---|---|---|---|---
`profession         `|`0`|`  1`|`  9`|` 33`
`organisations      `|`0`|`  1`|`  1`|` 13`
`social_surroundings`|`0`|`  1`|`  0`|` 14`
`target_audience    `|`0`|`  1`|`  0`|` 13`
`ti_knowledge       `|`0`|`  1`|`  0`|` 13`
`prof_growth        `|`0`|`  1`|`  0`|` 14`
---|---|---|---|---
`Score              `|` `|`   `|`   `|`   `
---|---|---|---|---
`a                  `|`0`|`  6`|`  2`|`  6`
`b                  `|`0`|`  6`|`  1`|`  5`
`r                  `|`0`|`100`|` 25`|` 92`
