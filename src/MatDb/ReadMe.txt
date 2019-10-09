
BASCULER TOUTE LA GESTION DE L'ETAT READ ONLY / TEXTE VIDE de l'edit dans CListBoxUpDown


--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG
Après création d'un nouveau fichier, lorsqu'on sort du mode édition, la liste déroulante "Fichier de données" 
	de l'onglet "Fichier" est vidée de son contenu. Les fichiers ne sont pas effacés ! Pour contourner ce bug, 
	en attendant sa correction, il suffit de quitter MatDb, et de le relancer. La liste est alors correctement remplie.
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG
Si on supprime toutes les catégories, la dernière reste affichée dans l'edit de la page Rechercher
il y a d'autres problèmes, dus au fait que la nuance et la catégorie courantes ne sont pas remis 
à NULL quand ces listes sont vides. Trouver où faire cette MAJ des pointeurs
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG TULADANLCU
dans une listboxupdown, quand on clique long pour drag & drop, le champ edit associé devrait être mis à jour sur WM_LBTUTTONDOWN
problème : la sélection d'une listbox se fait sur LBUTTONUP !
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Bug d'affichage lors de l'abandon d'un déplacement par "tap & hold" : la barre d'insertion ne s'efface pas complètement.
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
page Rechercher : problème de navigation avec la listbox : les flèches haut bas font passer le focus ailleurs (perte de focus de la listbox)
-> CEdit remplacé par CEditEx : le CEdit semble ganger le focus si on change son texte par programmation
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG KASTANANAFOUTE
numérotation des nouvelles nuances : le deuxième indice devrait être réactualisé en fonction (pas critique !!!)
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on sélectionne une catégorie dans la page Nuances, le focus de combo est perdu
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on ajoute une nouvelle catégorie, le champ d'édition de nuance n'est pas vide à la page "Nuances" ; idem si on sélectionne
	une catégorie dont la liste de nuances est vide ; donc pb de MAJ de l'edit sur liste de catégories vide
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on crée une catégorie, puis qu'on la supprime : "problème lié à gwes.exe"
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on crée une nuance alors que aucune catégorie n'est créée, problème : le bouton "+" devrait être désactivé si pas de nuance présente
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on supprime une catégorie avec nuances alors que c'est la seule : l'edit et la liste dans la page Nuances n'est pas vidée
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on supprime toutes les catégories, l'edit ID n'est pas vidé
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on crée un nouveau fichier, que toutes les pages ont été créées, qu'on ajoute une catégorie, puis qu'on ajoute une nuance
	la liste d'objets nommés des nuances n'est pas créée ou passée à la ListBoxUpDown 
	en revanche pas de problème si la page doit être créée (jamais consultée)
--------------------------------------------------------------------------------------------------------------------------------------------------------------
	
--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
si on passe en mode édition, l'edit de la page Classes reste à l'état "read only" tant qu'on ne sélectionne pas une catégorie
--------------------------------------------------------------------------------------------------------------------------------------------------------------

