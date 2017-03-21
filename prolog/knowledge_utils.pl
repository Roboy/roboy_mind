/* ***************************************
	Author:	Emilia Lozinska
	E-mail:	ga47nub@mytum.de

 This library contains predicates used for the 
 inference method using prolog queries. 

 NOTE: The following symbols are used to describe the parameter 
of the predicates
 + The argument is instantiated at entry.
 - The argument is not instantiated at entry.
 ? The argument is unbound or instantiated at entry.
*/

:- module(knowledge_utils,
    [
	save_object/5,
	get_properties/3,
	get_object/4
    ]).

:- use_module(library('semweb/rdfs')).
:- use_module(library('semweb/rdf_db')).
:- use_module(library('rdfs_computable')).

:- rdf_db:rdf_register_ns(knowrob, 'http://knowrob.org/kb/knowrob.owl#', [keep(true)]).
:- rdf_db:rdf_register_ns(semRoom_semantic_map, 'http://knowrob.org/kb/semRoom_semantic_map.owl#', [keep(true)]).

get_class_path(Class, Class_path) :-
	% We need to find out if the Class has URL or not
	((concat_atom(List, '#', Class),length(List,Length),Length>1) ->
	( % Class has already a URI
	   Class_path=Class );
	  % When the class does not have URL, will get the knowrob path
	(atom_concat('http://knowrob.org/kb/knowrob.owl#', Class, Class_path1),
	atom_concat('http://knowrob.org/kb/semRoom_semantic_map.owl#', Class, Class_path2),
	findall(A,owl_subclass_of(Class_path1,A),List),
	length(List,L),
    (L > 2) -> 
		atom_concat('http://knowrob.org/kb/knowrob.owl#', Class, Class_path);
	atom_concat('http://knowrob.org/kb/semRoom_semantic_map.owl#', Class, Class_path)
 	)).

assert_properties(Instance,Properties,Values) :-
	([P] = Properties) ->	
		[V] = Values,
		get_class_path(P, P_path),
		rdf_assert(Instance, P_path, V);
	([Head_P|Tail_P] = Properties) -> 
		[Head_V|Tail_V] = Values,
		get_class_path(Head_P, P_path),
		rdf_assert(Instance, P_path, Head_V),
		assert_properties(Instance,Tail_P,Tail_V);
	get_class_path(Properties, P_path),	
	rdf_assert(Instance, P_path, Values).

save_object(Class, ID, Properties, Values, Instance) :-
	create_instance_from_class(Class, ID, Instance),
	assert_properties(Instance,Properties,Values).

get_properties([],[],Instance) :- write('Empty'),!.

get_properties(Properties,Values,Instance) :-
	([_] = Properties) ->	
		[P] = Properties,
		get_class_path(P, P_path),	
		[V] = Values,
		owl_has(Instance, P_path, V);
	([_|_] = Properties) -> 
		[Head_P|Tail_P] = Properties,
		[Head_V|Tail_V] = Values,
		get_class_path(Head_P, P_path),	
		owl_has(Instance, P_path, V),
		get_properties(Tail_P,Tail_V,Instance);
	get_class_path(Head_P, P_path),	
	owl_has(Instance, P_path, V).

get_object(Properties, Values, Class, Instance) :-
	get_properties(Properties,Values,Instance),
	rdfs_individual_of(Instance,Class),!.