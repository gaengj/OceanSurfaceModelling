#! /usr/bin/env python
# -*- coding: utf8 *-*

import sys
import os.path
import subprocess
import shutil
import tempfile
import string
import argparse

class ClassInfo:
    classe = ""
    template = False
    def __init__( self, classe, template ):
        self.classe = classe
        self.template = template

class QuestionATester:
    classes = [] # list of ClassInfo
    extra_includes = [] # extra includes needed
    sub_tests = dict()
    points = 0
    depends = []
    def __init__( self, classes, extra_includes, sub_tests, depends ):
        self.classes = classes[:]
        self.extra_includes = extra_includes[:]
        self.sub_tests = sub_tests.copy()
        self.depends = depends[:]
        self.points = 0

    @staticmethod
    def getSingleTest( lines_of_code ):
        return { "" : lines_of_code[:] }

def QuestionKey( val ):
    #return str(val), leads to questions_par_tp[i] being badly ordered
    return val
def QuestionList( vallist ):
    res = []
    for val in vallist:
        res.append( QuestionKey( val ) )
    return res

AccessorIndexAreFromOneToN = False
AccessorParenthesisUsed = True

def VectorAccessor( obj, index ):
    paramIndex = index+1 if AccessorIndexAreFromOneToN else index
    if AccessorParenthesisUsed:
        return obj + "(" + str(paramIndex) + ")"
    else:
        return obj + "[" + str(paramIndex) + "]"

def MatrixAccessor( obj, i, j ):
    paramIndexi = i+1 if AccessorIndexAreFromOneToN else i
    paramIndexj = j+1 if AccessorIndexAreFromOneToN else j
    if AccessorParenthesisUsed:
	    return obj + "(" + str(paramIndexi) + "," + str(paramIndexj) + ")"
    else:
        return obj + ".at(" + str(paramIndexi) + "," + str(paramIndexj) + ")"

# Pour chaque question de chaque TP:
questions_par_tp = { \
    1 : # TP1
    {
        QuestionKey(1) : # Question1
            QuestionATester([ClassInfo('Dvector',False)], # Files, classes tested
                            [],
                            QuestionATester.getSingleTest(['Dvector v1',
                                                           'Dvector v2(3)',
                                                           'Dvector v3(3,0)',
                                                           'v1.display(std::cout)']), # Test code
                            []), # dependencies
        QuestionKey(2) :
            QuestionATester([ClassInfo('Dvector',False)],
                            [],
                            QuestionATester.getSingleTest(['Dvector v1',
                                                           'Dvector v2(v1)',
                                                           'int i = v1.size()',
                                                           'v2.fillRandomly()']),
                            QuestionList([1])),
        QuestionKey(3) :
            QuestionATester([ClassInfo('Dvector',False)],
                            [],
                            QuestionATester.getSingleTest(['std::string file',
                                                           'Dvector v1(file)']),
                            QuestionList([1]))
    },
    2 : # TP2
    {
        QuestionKey(1) :
            QuestionATester([ClassInfo('Dvector',False)],
                            [],
                            QuestionATester.getSingleTest(['Dvector v1',
                                                           'Dvector v2(3)',
                                                           'Dvector v3(3,0)',
                                                           'int i = v1.size()',
                                                           'v1.display(std::cout)',
                                                           'v1.fillRandomly()']),
                            []),
        QuestionKey(2) :
            QuestionATester([ClassInfo('Dvector',False)],
                            [],
                            QuestionATester.getSingleTest(['Dvector v1(1)',
                                                           VectorAccessor( "v1", 0 ) + ' = 0.0',
                                                           'const Dvector v2(1)',
                                                           'double val = ' + VectorAccessor( "v2", 0 )]),
                            QuestionList([1])),
        QuestionKey(3) :
            QuestionATester([ClassInfo('Dvector',False)],
                            [],
                            QuestionATester.getSingleTest(['Dvector v1, v2',
                                                           'v1+2.0',
                                                           'v1-2.0',
                                                           'v1*2.0',
                                                           'v1/2.0',
                                                           'v1+v2',
                                                           'v1-v2',
                                                           '-v1']),
                            QuestionList([1])),
        QuestionKey(4) :
            QuestionATester([ClassInfo('Dvector',False)],
                            [],
                            QuestionATester.getSingleTest(['Dvector v1',
                                                           'std::cout << v1',
                                                           'Dvector v2',
                                                           'std::cin >> v2']),
                            QuestionList([1])),
        QuestionKey(5) :
            QuestionATester([ClassInfo('Dvector',False)],
                            [],
                            QuestionATester.getSingleTest(['Dvector v1',
                                                           'Dvector v2',
                                                           'v1+=2.0',
                                                           'v1-=2.0',
                                                           'v1*=2.0',
                                                           'v1/=2.0',
                                                           'v1+=v2',
                                                           'v1-=v2']),
                            QuestionList([1])),
        QuestionKey(6) :
            QuestionATester([ClassInfo('Dvector',False)],
                            [],
                            QuestionATester.getSingleTest(['Dvector v1',
                                                           'Dvector v2',
                                                           'v1 = v2']),
                            QuestionList([1])),
        QuestionKey(7) :
            QuestionATester([ClassInfo('Dvector',False)],
                            [],
                            QuestionATester.getSingleTest(['Dvector v1',
                                                           'Dvector v2',
                                                           'bool same = (v1 == v2)']),
                            QuestionList([1]))
    }
}

bareme_auto = 0
note_totale = 0
copySourcesLocally = False # if True, files are copied to ./verification/src,
                           # else, they are used directly from ./src folder
optimizeSourcesCompilation = True # If True, some .o files are shared between all verification tests
extension = ".tar.gz"

def getFileExtension( archive ):
    if len(archive) > len(extension):
        return archive[-len(extension):]
    else:
        return ""

def getFileBaseName( archive ):
    if len(archive) > len(extension) and getFileExtension( archive ) == extension:
        return os.path.basename(archive[:len(archive)-len(extension)])
    else:
        return os.path.splitext( os.path.basename(archive) )[0]

class term_colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

    @staticmethod
    def colored( str, color ):
        return color + str + term_colors.ENDC

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL = ''
        self.ENDC = ''

def checkName( nom, quoi, tpinfo ):
    noms = string.split( os.path.basename(nom), '_' )
    valid = False
    # get TP number + names
    while len(noms) > 0:
        nom = noms[0]
        noms.pop(0)
        if len(nom) == 3 and nom[:2].upper() == "TP":
            try:
                tpinfo[0] = int(nom[2])
                valid = True
            except ValueError:
                valid = False
            break
    # check TP number
    if valid and not tpinfo[0] in questions_par_tp.keys():
        valid = False

    # copy names
    if len(noms) == 1 or len(noms) == 2:
        tpinfo[1] = noms[:]
    else:
        valid = False

    # report errors
    if not valid:
        if quoi != "":
            print term_colors.colored( "Le nom de " + quoi + " doit impérativement être 'TPi_login1' ou 'TPi_login1_login2'", term_colors.FAIL )
    return valid

def getSubFolderName( tpinfo ):
    res = "TP" + str(tpinfo[0])
    for eleve in tpinfo[1]:
        res += "_" + eleve
    return res

def getSubFolderNameFromArchive( archive ):
    tpinfo = [ 0, [] ]
    if checkName( getFileBaseName(archive), "", tpinfo ):
        return getSubFolderName(tpinfo)
    else:
        return ""

def createMakefile( folder, project, files, includes ):
    makefile = open(os.path.join( folder, "Makefile" ), 'w')
    makefile.write( "PROG = " + project + "\n" )
    objs = []
    cpps = []
    for filename in files:
        cfile = filename
        if not copySourcesLocally:
            ofile = os.path.splitext(filename)[0] + ".o"
            os.path.dirname(cfile)
            if optimizeSourcesCompilation and os.path.dirname(cfile) == "../../src":
                # save o file to parent folder so that it's shared between all compiled tests
                ofile = os.path.join( "..", os.path.basename(ofile) )
            else:
                # save o file locally
                ofile = os.path.basename(ofile)
        else:
            ofile = os.path.splitext(os.path.basename(filename))[0] + ".o"
        objs.append( ofile )
        cpps.append( cfile )

    makefile.write( "OBJS = " + " ".join( objs ) + "\n" )
    makefile.write( "CPPS = " + " ".join( cpps ) + "\n" )
    makefile.write( "CC = g++\n" )
    cxxExtraFlags = ""
    if AccessorIndexAreFromOneToN:
        cxxExtraFlags += " -DPYTHON_TESTS_INDEX_ONE_TO_SIZE"
    if AccessorParenthesisUsed:
        cxxExtraFlags += " -DPYTHON_TESTS_USE_PARENTHESIS_OPERATOR"
    makefile.write( "CXXFLAGS = -Wall -g -std=c++11" + cxxExtraFlags + "\n" )
    incs = ""
    for folder in includes:
        incs += " -I" + folder
    makefile.write( "INCS =" + incs + "\n" )
    makefile.write( "\n" )

    if not copySourcesLocally: # Need specific build instructions
        makefile.write( "default: $(PROG)\n" )
        if optimizeSourcesCompilation:
            for fileindex in range(len(objs)):
                makefile.write( objs[fileindex] + ": " + cpps[fileindex] + "\n" )
                makefile.write( "\t$(CC) $(CXXFLAGS) $(INCS) -c " + cpps[fileindex] + " -o " + objs[fileindex] + "\n" )
        else:
            # This creates .o files locally, let's try to share them upon all projects
            makefile.write( "$(OBJS): $(CPPS)\n" )
            makefile.write( "\t$(CC) $(CXXFLAGS) $(INCS) -c $(CPPS)\n" )

    makefile.write( "$(PROG): $(OBJS)\n" )
    makefile.write( "\t$(CC) $(CXXFLAGS) -o $@ $(OBJS)\n" )
    makefile.close()

def doSubTest( tp, questionATester, questionStr, lines_of_code, verif_folder, src_folder, folder_to_test, delete_target_folder, showDetails ):
    test_folder = os.path.join( verif_folder, "question" + str(questionStr) )
    if ( os.path.isdir( test_folder ) ):
        shutil.rmtree( test_folder )
    os.makedirs(test_folder)

    # Check, copy student cpp/h files to folder
    for filebase in questionATester.classes:
        files_to_test = []
        if not filebase.template:
            files_to_test.append( filebase.classe + ".cpp" )
        files_to_test.append( filebase.classe + ".h" )
        for file_to_test in files_to_test:
            file_absolute_path = os.path.join( "src", file_to_test )
            file_full_path = os.path.join( folder_to_test, file_absolute_path )
            target_file = os.path.join( test_folder, file_to_test )
            if not os.path.isfile( file_full_path ):
                print term_colors.colored( "Le fichier " + file_full_path + " n'existe pas!", term_colors.FAIL )
                shutil.rmtree( test_folder )
                return [0,False]
            else:
                if copySourcesLocally:
                    shutil.copy( file_full_path, target_file )

    # Create Makefile
    src_path = "../../src"
    target_program = "test_tp" + str(tp) + "_question" + str(questionStr)
    files = []
    for source in questionATester.classes:
        the_cpp_file = source.classe + ".cpp"
        if not source.template:
            if copySourcesLocally:
                files.append( the_cpp_file ) # change path
            else:
                files.append( os.path.join(src_path, the_cpp_file) ) # change path
    files.append( "main.cpp" ) # add main.cpp to the list
    createMakefile( test_folder, target_program, files, [src_path] )

    # Create test file
    testfile = open(os.path.join( test_folder, "main.cpp" ), 'w')
    testfile.write( "#include <cstdlib>\n" )
    testfile.write( "#include <cstdio>\n" )
    testfile.write( "#include <iostream>\n" )
    testfile.write( "#include <fstream>\n" )
    for extra_include in questionATester.extra_includes:
        testfile.write( "#include " + extra_include + "\n" ) # extra includes
    for filebase in questionATester.classes:
        testfile.write( "#include \"" + filebase.classe + ".h\"\n" ) # compile cpp on the fly
    testfile.write( "\n" )
    testfile.write( "int main()\n" )
    testfile.write( "{\n" )
    to_compile = ""
    for statement in lines_of_code:
        to_compile += "\t" + statement + ";\n"
    testfile.write( to_compile )
    testfile.write( "\treturn 0;\n" )
    testfile.write( "}\n" )
    testfile.close()

    # Compile
    note = 0
    compiled = False
    buildfilename = os.path.join( test_folder, 'build.log' )
    errorfilename = os.path.join( test_folder, 'build_err.log' )
    with open( buildfilename, "w") as outfile:
        with open( errorfilename, "w") as errfile:
            old_path = os.getcwd()
            os.chdir(test_folder)
            if subprocess.call(["make"], stdout=outfile, stderr=errfile) == 0 and os.path.isfile( target_program ):
                # Project could be compiled!!
                note = questionATester.points
                compiled = True
            os.chdir(old_path)
            if compiled and copySourcesLocally: # save files that compiled for later use (notation)
                for filebase in questionATester.classes:
                    if not filebase.template:
                        shutil.copy( os.path.join( test_folder, filebase.classe + ".cpp"), src_folder )
                    shutil.copy( os.path.join( test_folder, filebase.classe + ".h"), src_folder )

    if compiled:
        shutil.rmtree( test_folder )
    else:
        message = "Le test de vérification de la question " + str(questionStr) + " n'a pas compilé!"
        if showDetails:
            message += " vérifiez que tous les points sont traités et que la syntaxe est correcte"
        print term_colors.colored( message, term_colors.FAIL )
        if showDetails:
            if delete_target_folder:
                message += "\nLe test va être supprimé, pour le conserver (afin de comprendre pourquoi il ne compile pas), " +\
                           "précisez un dossier de sortie (--output) à l'exécution du script"
            else:
                message += "\nPour voir le code du test, rendez-vous dans ce dossier " + test_folder
            print "\nCompilation de:\n" + to_compile
            with open(errorfilename,'r') as f:
                print "Erreur reportée:\n" + f.read()

    return [note,compiled]

def QuestionName( question, sub_test, compilerSafe ):
    name = str(question)
    if str(sub_test) != "":
        if not compilerSafe:
            name += "."
        name += str(sub_test)
    return name

def bareme( tp, target_folder, folder_to_test, delete_target_folder, delete_verif_folder, showDetails ):
    note_max = 0
    nombre_de_points_total = 0

    for question in questions_par_tp[tp].keys():
        nombre_de_points_total += questions_par_tp[tp][question].points

    verif_folder = os.path.join( folder_to_test, "verification" )
    if ( os.path.isdir( verif_folder ) ):
        print term_colors.colored( "Le dossier " + verif_folder + " existe déjà, merci de le supprimer", term_colors.FAIL )
        return [0,nombre_de_points_total]
    os.makedirs(verif_folder)

    src_folder = ""
    if copySourcesLocally:
        src_folder = os.path.join( verif_folder, "src" )
        if ( os.path.isdir( src_folder ) ):
            shutil.rmtree( src_folder )
        os.makedirs(src_folder)
        done = open( os.path.join( src_folder, "done.h" ), "w" )
    else:
        done = open( os.path.join( verif_folder, "done.h" ), "w" )

    if copySourcesLocally:
        done.write( "#define SOURCES_COPIED\n" )

    valid = set()
    for question in questions_par_tp[tp].keys():
        pre_requisit_ok = True
        questionATester = questions_par_tp[tp][question]
        for needed in questionATester.depends:
            if not needed in valid:
                print term_colors.colored( "La question " + str(question) + " ne pourra pas être testée, car la question " + str(needed) + " n'a pas été traitée, elle risque de ne pas vous rapportera de points", term_colors.FAIL )
                pre_requisit_ok = False
                break

        if pre_requisit_ok:
            for sub_test in sorted(questionATester.sub_tests.keys()):
                questionStr = QuestionName(question,sub_test,False)
                res = doSubTest( tp, questionATester, questionStr, questionATester.sub_tests[sub_test], verif_folder, src_folder, folder_to_test, delete_target_folder, showDetails )
                if ( not res[1] ):
                    print term_colors.colored( "La question " + questionStr + " ne pourra pas être testée, elle risque de ne pas vous rapportera de points", term_colors.FAIL )
                else:
                    valid.add( question )
                    print term_colors.colored( "La question " + questionStr + " pourra être testée, elle pourra vous rapporter des points", term_colors.OKGREEN )
                    done.write( "#define TP" + str(tp) + "_QUESTION" + QuestionName(question,sub_test,True) + "_DONE\n" )
                    #done.write( "#define TP" + str(tp) + "_QUESTION" + QuestionName(question,sub_test,True) + "_SCALE " + str(res[0]) + "\n" )
                note_max += res[0]

    done.close()

    if delete_verif_folder:
        print "Suppression de " + verif_folder
        shutil.rmtree( verif_folder )

    return [note_max,nombre_de_points_total]

def verify_folder_or_archive( param, output, keep_verif_folder, showDetails ):

    print 'Vérification de ' + os.path.basename(param)

    folder_to_test = param
    isFolderReady = os.path.isdir(param)

    tpinfo = [ 0, [] ]
    what = "le dossier" if isFolderReady else "l'archive"
    validName = checkName( getFileBaseName(os.path.basename(param)), what, tpinfo )
    binomes = tpinfo[1]
    if len(binomes) != 0:
        message = what.capitalize() + " contient le rapport de TP" + (str(tpinfo[0]) if tpinfo[0] != 0 else "") + " de "
        message += " et ".join( term_colors.colored( eleve, term_colors.OKGREEN ) for eleve in binomes )
        if len(binomes) == 1:
            message += " " + term_colors.colored( "seul (sans binôme)", term_colors.FAIL )
        print message
    if not validName:
        print term_colors.colored( "Nom d'archive invalide", term_colors.FAIL )
        return 0

    delete_target_folder = False
    # Delete verif folder if working on a folder, keep it if working on an archive (notation flow)
    delete_verif_folder = isFolderReady and (not keep_verif_folder)

    if not isFolderReady:
        # An archive was given as parameter, extract it to a folder
        fileext = getFileExtension( param )
        filename = getFileBaseName( param )

        if not os.path.isfile( param ):
            print term_colors.colored( "Fichier/dossier " + param + " introuvable", term_colors.FAIL )
        elif filename == "" or fileext != extension:
            print term_colors.colored( "Extension invalide (doit être " + extension + ")", term_colors.FAIL )
        else:
            if output != "":
                target_folder = output
                if not os.path.exists(target_folder):
                    os.makedirs(target_folder)
                else:
                    print term_colors.colored( "Le dossier " + target_folder + " existe déjà, supprimez-le", term_colors.FAIL )
                    quit()
                delete_target_folder = False
            else:
                target_folder = tempfile.mkdtemp(filename, "temp_verif_tp")
                delete_target_folder = True
            print "Extraction de l'archive vers " + target_folder + "..."
            copied_archive = os.path.join(target_folder, os.path.basename(param) )
            shutil.copy( param, copied_archive )
            with open( os.path.join( target_folder, 'tar.log' ), "w") as outfile:
                if subprocess.call(["tar", "xvzf", copied_archive, "-C", target_folder ], stdout=outfile) == 0:
                    print "L'archive a pu être extraite"
                    sub_folders = filter(os.path.isdir, [os.path.join(target_folder,f) for f in os.listdir(target_folder)])
                    expectedfoldername = getSubFolderName(tpinfo)
                    if len(sub_folders) == 1:
                        if os.path.basename(sub_folders[0]).lower() == expectedfoldername.lower():
                            folder_to_test = sub_folders[0]
                            isFolderReady = True
                        else:
                            print term_colors.colored( "L'archive " + param + " doit contenir un dossier nommé " + expectedfoldername, term_colors.FAIL )
                    else:
                        print term_colors.colored( "L'archive doit impérativement contenir un et un seul dossier nommé " + expectedfoldername, term_colors.FAIL )
                else:
                    print term_colors.colored( "L'archive n'a pas pu être décompressée", term_colors.FAIL )
    else:
        target_folder = folder_to_test
        if output != "":
            print term_colors.colored( "Le paramètre de sortie ne peut être précisé lorsqu'un dossier est testé", term_colors.FAIL )
            quit()

    isFolderValid = False
    if isFolderReady:
        folder_to_test = folder_to_test.rstrip( "/" )
        print 'Le dossier ' + folder_to_test + ' va être analysé'
        folder_name = os.path.basename(folder_to_test)
        isFolderValid = checkName( folder_name, "le dossier", tpinfo )

    note_max = 0

    if isFolderValid:
        bareme_output = bareme( tpinfo[0], target_folder, folder_to_test, delete_target_folder, delete_verif_folder, showDetails )
        if bareme_output[1] != 0 and bareme_auto != 0 and note_totale != 0:
            bareme_manuel = note_totale - bareme_auto
            note_max = bareme_output[0]*bareme_auto/bareme_output[1]
            if ( note_max == 0 ):
                print "-> Votre code ne vous rapportera aucun point"
            else:
                print "-> Si votre code s'exécute correctement (tests comportemental), vous pourrez gagner " +\
                      str(note_max) + " points sur " + str(bareme_auto)
            print "-> La relecture de votre rapport et de votre code pourront vous rapporter " +\
                  str(bareme_manuel) + " points "
            note_max = bareme_manuel + note_max
            if ( note_max == note_totale ):
                color = term_colors.OKGREEN
            else:
                color = term_colors.FAIL
            print "-> Votre note sera donc comprise entre " + term_colors.colored( str(0), color ) + " et " + term_colors.colored( str( note_max ), color )
    #else:
    #    print "-> Votre note sera " + term_colors.colored( str(note_max), term_colors.FAIL )

    if delete_target_folder:
        print "Le dossier temporaire " + target_folder + " va être supprimé."
        print "Précisez un nom de dossier de destination sur la ligne de commande (exemple: --output toto) pour qu'il soit conservé"
        shutil.rmtree(target_folder)

    return note_max

def verify():
    parser = argparse.ArgumentParser(description="Verification d'une archive ou d'un dossier de TP.")
    parser.add_argument('input',  metavar='archive|dossier', type=str,
                        help='une archive (tar.gz) ou un dossier')
    parser.add_argument('--output', metavar='destination', required=False, type=str, default='', nargs=1,
                        help='Uniquement pour la vérfication d\'une archive: dossier de sortie (un dossier temporaire sera utilisé si non précisé)')
    parser.add_argument('-keep_verif_folder', action='store_true', help="Uniquement pour la vérification d\'un dossier: conserve le dossier de \"verification\" plutôt que de le supprimer (pour la vérification d\'une archive, et si --output est précisé, le dossier n'est jamais supprimé)")
    parser.add_argument('-silent', action='store_true', help="Reporte juste les erreurs, sans afficher le code qui ne compile pas")
    args = parser.parse_args()

    output = ""
    if len(args.output) == 1:
        output = args.output[0]

    return verify_folder_or_archive( os.path.realpath(args.input), output, args.keep_verif_folder, not args.silent )

if __name__ == "__main__":
    sys.exit( verify() )

