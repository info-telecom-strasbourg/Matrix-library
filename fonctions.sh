#
# Ce fichier contient des définitions communes à tous les tests
#

set -u

PROG=${PROG:-./distribuer}
V="valgrind -q --leak-check=full --error-exitcode=1"

TMPDIR=/tmp/tps-tp.$$	# répertoire de test
TMPRES=/tmp/tps-tp.$$	# sortie du test

# trap "rm -rf $DIR $RES" EXIT	# pour supprimer les fichiers à la sortie

annoncer ()
{
    COURANT="$1"
    coloredEcho "==== $1 ====" blue
    echo "
####
#### $1
####" >> $LOG
}

fail ()
{
    coloredEcho "==> Échec du test '$COURANT'" red
    coloredEcho "==> Voir le fichier ./$TESTDIR/$LOG" red
    coloredEcho "==> Exit" red
    exit 1
}

##############################################################################
# une sorte de chronomètre
#
# La commande date ne permet pas de récupérer l'heure avec une précision
# supérieure à la seconde (si l'on s'en tient à POSIX). On se fait donc
# la nôtre.
#

CHRONO=$TMPDIR/chrono	# notre chronomètre

init_chrono ()
{
    cat > $CHRONO.c <<'EOF'
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <sys/time.h>

/*
 * Un petit programme pour implémenter un chronomètre :
 * Syntaxe :
 *	./a.out			// affiche la date correspondant à maintenant
 *	./a.out t1		// affiche la durée entre t1 et maintenant
 *	./a.out t1 min max	// code retour = 0 si durée \in [min, max]
 *
 */


typedef long double temps ;	// un point dans le temps ou une durée

temps lire_temps (const char *str)
{
    temps t ;
    int n ;

    n = sscanf (str, "%Lf", &t) ;
    if (n == 0)
    {
	fprintf (stderr, "date invalide (%s)\n", str) ;
	exit (1) ;
    }
    return t ;
}

temps duree (const char *str)
{
    struct timeval tv ;
    temps t1, t2 ;

    t1 = lire_temps (str) ;
    gettimeofday (&tv, NULL) ;
    t2 = tv.tv_sec + tv.tv_usec / 1000000.0 ;
    return t2 - t1 ;
}

int main (int argc, char *argv [])
{
    struct timeval tv ;
    temps d ;
    temps min, max ;
    int r = 0 ;

    switch (argc)
    {
	case 1 :	// démarrer le chrono
	    gettimeofday (&tv, NULL) ;
	    printf ("%jd.%06jd\n", (intmax_t)tv.tv_sec, (intmax_t)tv.tv_usec) ;
	    break ;

	case 2 :	// durée
	    d = duree (argv [1]) ;
	    printf ("%Lf\n", d) ;
	    break ;

	case 4 :	//
	    d = duree (argv [1]) ;
	    min = lire_temps (argv [2]) ;
	    max = lire_temps (argv [3]) ;
	    if (d < min)
	    {
		fprintf (stderr, "durée %Lf < %Lf\n", d, min) ;
		r = 1 ;
	    }
	    if (d > max)
	    {
		fprintf (stderr, "durée %Lf > %Lf\n", d, max) ;
		r = 1 ;
	    }
	    printf ("%Lf ok\n", d) ;
	    break ;

	default :
	    fprintf (stderr, "usage: %s [debut [min max]]\n", argv [0]) ;
	    r = 1 ;
	    break ;

    }
    exit (r) ;
}
EOF
    cc -Wall -Wextra -Werror -o $CHRONO $CHRONO.c
}

# Démarrer le chronomètre
chrono_start ()
{
    if [ ! -f $CHRONO ]
    then init_chrono
    fi
    CHRONO_DEBUT=$($CHRONO)
}

# Arrêter le chronomètre et vérifier que la durée passée en paramètre
# est dans l'intervalle spécifié
# code retour = 0 ou 1
chrono_stop ()
{
    local min="$1" max="$2"
    $CHRONO $CHRONO_DEBUT "$min" "$max"
}

chrono_duree ()
{
    $CHRONO $CHRONO_DEBUT
}

# créer un fichier de taille et de nom indiqués
creer_fichier ()
{
    local taille="$1" nom="$2"

    dd if=/dev/zero of=$nom bs=$taille count=1 2> /dev/null
}
# Normaliser la sortie (supprimer espaces superflus gênant la comparaison)
normaliser ()
{
    sed -e 's/[ 	][ 	]*/ /g' -e 's/^ //'
}

# Renvoie l'ordre dans lequel les fils se terminent
# le résultat du programme à tester doit être présenté sur l'entrée standard
# Cette fonction renvoie la liste des fils (ex: 1 1 2) sur la sortie standard
ordre ()
{
    local liste

    liste=$(normaliser | sed 's/ .*//')
    echo $liste
}

# Fonctions de test:
# prend en argument 1 un fichier contenant la sortie du programme
# prend en argument 2 le texte attendu

test_grep()
{
  cat "$1" | grep "$2"
}

test_diff()
{
  echo "$2" | diff "$1" -
}


test_entree_sortie ()
{
  STDIN=$1
  ATTENDU=$2
  FONCTION_TEST=$3
  SORTIE=/tmp/tps-c.out.$$

  # execute le programme, conserve la sortie (stdout et stderr confondu)
  echo "
#### Execution" >> $LOG
  echo "$STDIN" | ./$TARGET 2>&1 > $SORTIE
  EXITCODE=$?

  # conserve la sorte dans le log
  cat $SORTIE >> $LOG
  echo "==> exitcode: $EXITCODE" >> $LOG

  if [ $EXITCODE -ne 0 ]
  then
    fail
  fi


  # Compare avec l'attendu

  echo "
#### Comparaison" >> $LOG
  $FONCTION_TEST "$SORTIE" "$ATTENDU" >> $LOG
  if [ $? -ne 0 ]
  then
    fail
  else
    coloredEcho "OK" green
  fi
}

test_fichiers_entree_sortie ()
{
  STDIN=$(cat $1)
  ATTENDU=$(cat $2)
  test_entree_sortie "$STDIN" "$ATTENDU" "$3"
}

if [ -z ${COLORIZE+x} ]; then
  COLORIZE=1
fi

coloredEcho ()
{
    local exp="$1";
    local color=$2;



     case $(echo $color | tr '[:upper:]' '[:lower:]') in
      black) color=16 ;;
      red) color=5 ;;
      green) color=2 ;;
      yellow) color=3 ;;
      blue) color=4 ;;
      orange) color=1 ;;
      cyan) color=6 ;;
      gray) color=8 ;;
      white|*) color=15 ;; # white or invalid color
     esac
     if [ $COLORIZE -eq 1 ]; then
      tput setaf $color;
      echo "$exp";
      tput sgr0;
    else
      echo "$exp";
    fi
}
#set -x
