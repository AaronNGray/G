#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "g/LexicalAnalyserGenerator/LexicalMachine.h"
#include "g/LexicalAnalyserGenerator/LexicalContext.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/Actions.h"

using namespace G::LexicalAnalyserGenerator;

FileName filename("lg");
LexicalGenerator* lg_LexicalGenerator = new LexicalGenerator(filename, new LexicalMachine("lg", false, {
  new LexicalContext("INITIAL", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSequence(
                        RegularGrammar::newSequence(
                          RegularGrammar::newSequence(
                            RegularGrammar::newSequence(
                              RegularGrammar::newSequence(
                                RegularGrammar::newCharacterClass(CharacterClass( Char('l'))),
                                RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                              ),
                              RegularGrammar::newCharacterClass(CharacterClass( Char('x')))
                            ),
                            RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                          ),
                          RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                        ),
                        RegularGrammar::newEnd(0)
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newSequence(
                          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('A', 'Z'), Char('_'), Range('a', 'z')}))),
                          RegularGrammar::newKleene(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'Z'), Char('_'), Range('a', 'z')})))
                          )
                        ),
                        RegularGrammar::newEnd(1)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('{'))),
                      RegularGrammar::newEnd(2)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('}'))),
                    RegularGrammar::newEnd(3)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                    RegularGrammar::newCharacterClass(CharacterClass( Char('*')))
                  ),
                  RegularGrammar::newEnd(4)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/')))
                ),
                RegularGrammar::newEnd(5)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')}))),
                RegularGrammar::newKleene(
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')})))
                )
              ),
              RegularGrammar::newEnd(6)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(7)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(8)
        )
      )
    )
  ),
  new LexicalContext("LEXER", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSelection(
                            RegularGrammar::newSelection(
                              RegularGrammar::newSelection(
                                RegularGrammar::newSelection(
                                  RegularGrammar::newSelection(
                                    RegularGrammar::newSelection(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newSequence(
                                                  RegularGrammar::newSequence(
                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('c'))),
                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                  ),
                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                                ),
                                                RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                              ),
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                            ),
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('x')))
                                          ),
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                        ),
                                        RegularGrammar::newEnd(9)
                                      ),
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newCharacterClass(CharacterClass( Char('s'))),
                                                RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                              ),
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                            ),
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                          ),
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                        ),
                                        RegularGrammar::newEnd(10)
                                      )
                                    ),
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('c'))),
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                          ),
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('d')))
                                        ),
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                      ),
                                      RegularGrammar::newEnd(11)
                                    )
                                  ),
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('h'))),
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                            ),
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                          ),
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('d')))
                                        ),
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                      ),
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                    ),
                                    RegularGrammar::newEnd(12)
                                  )
                                ),
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newSequence(
                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('b'))),
                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                                ),
                                                RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                              ),
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                            ),
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('c')))
                                          ),
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('l')))
                                        ),
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                      ),
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                    ),
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                  ),
                                  RegularGrammar::newEnd(13)
                                )
                              ),
                              RegularGrammar::newSequence(
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('r'))),
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                            ),
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                          ),
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                        ),
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                      ),
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('y')))
                                    ),
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('p')))
                                  ),
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                ),
                                RegularGrammar::newEnd(14)
                              )
                            ),
                            RegularGrammar::newSequence(
                              RegularGrammar::newSequence(
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('v'))),
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                            ),
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('l')))
                                          ),
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('u')))
                                        ),
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                      ),
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                    ),
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('y')))
                                  ),
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('p')))
                                ),
                                RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                              ),
                              RegularGrammar::newEnd(15)
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newSequence(
                              RegularGrammar::newSequence(
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('r'))),
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                            ),
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                          ),
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('u')))
                                        ),
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                      ),
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                    ),
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                  ),
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('y')))
                                ),
                                RegularGrammar::newCharacterClass(CharacterClass( Char('p')))
                              ),
                              RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                            ),
                            RegularGrammar::newEnd(16)
                          )
                        ),
                        RegularGrammar::newSequence(
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('A', 'Z'), Char('_'), Range('a', 'z')}))),
                            RegularGrammar::newKleene(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'Z'), Char('_'), Range('a', 'z')})))
                            )
                          ),
                          RegularGrammar::newEnd(17)
                        )
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                        RegularGrammar::newEnd(18)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('{'))),
                      RegularGrammar::newEnd(19)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('}'))),
                    RegularGrammar::newEnd(20)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                    RegularGrammar::newCharacterClass(CharacterClass( Char('*')))
                  ),
                  RegularGrammar::newEnd(21)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/')))
                ),
                RegularGrammar::newEnd(22)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')}))),
                RegularGrammar::newKleene(
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')})))
                )
              ),
              RegularGrammar::newEnd(23)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(24)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(25)
        )
      )
    )
  ),
  new LexicalContext("CONTEXT", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSequence(
                        RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                        RegularGrammar::newEnd(26)
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                        RegularGrammar::newEnd(27)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('{'))),
                      RegularGrammar::newEnd(28)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('}'))),
                    RegularGrammar::newEnd(29)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                    RegularGrammar::newCharacterClass(CharacterClass( Char('*')))
                  ),
                  RegularGrammar::newEnd(30)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/')))
                ),
                RegularGrammar::newEnd(31)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')}))),
                RegularGrammar::newKleene(
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')})))
                )
              ),
              RegularGrammar::newEnd(32)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(33)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(34)
        )
      )
    )
  ),
  new LexicalContext("RE", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSelection(
                            RegularGrammar::newSelection(
                              RegularGrammar::newSelection(
                                RegularGrammar::newSelection(
                                  RegularGrammar::newSelection(
                                    RegularGrammar::newSelection(
                                      RegularGrammar::newSelection(
                                        RegularGrammar::newSelection(
                                          RegularGrammar::newSelection(
                                            RegularGrammar::newSelection(
                                              RegularGrammar::newSelection(
                                                RegularGrammar::newSelection(
                                                  RegularGrammar::newSelection(
                                                    RegularGrammar::newSelection(
                                                      RegularGrammar::newSelection(
                                                        RegularGrammar::newSelection(
                                                          RegularGrammar::newSelection(
                                                            RegularGrammar::newSelection(
                                                              RegularGrammar::newSequence(
                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                                                                RegularGrammar::newEnd(35)
                                                              ),
                                                              RegularGrammar::newSequence(
                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('['))),
                                                                RegularGrammar::newEnd(36)
                                                              )
                                                            ),
                                                            RegularGrammar::newSequence(
                                                              RegularGrammar::newCharacterClass(CharacterClass( Char('|'))),
                                                              RegularGrammar::newEnd(37)
                                                            )
                                                          ),
                                                          RegularGrammar::newSequence(
                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('*'))),
                                                            RegularGrammar::newEnd(38)
                                                          )
                                                        ),
                                                        RegularGrammar::newSequence(
                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('+'))),
                                                          RegularGrammar::newEnd(39)
                                                        )
                                                      ),
                                                      RegularGrammar::newSequence(
                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('?'))),
                                                        RegularGrammar::newEnd(40)
                                                      )
                                                    ),
                                                    RegularGrammar::newSequence(
                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('('))),
                                                      RegularGrammar::newEnd(41)
                                                    )
                                                  ),
                                                  RegularGrammar::newSequence(
                                                    RegularGrammar::newCharacterClass(CharacterClass( Char(')'))),
                                                    RegularGrammar::newEnd(42)
                                                  )
                                                ),
                                                RegularGrammar::newSequence(
                                                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'Z'), Range('a', 'z')}))),
                                                  RegularGrammar::newEnd(43)
                                                )
                                              ),
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newSequence(
                                                  RegularGrammar::newSequence(
                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                                    RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('X'), Char('x')})))
                                                  ),
                                                  RegularGrammar::newSequence(
                                                    RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')}))),
                                                    RegularGrammar::newKleene(
                                                      RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')})))
                                                    )
                                                  )
                                                ),
                                                RegularGrammar::newEnd(44)
                                              )
                                            ),
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                                RegularGrammar::newSequence(
                                                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')}))),
                                                  RegularGrammar::newKleene(
                                                    RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')})))
                                                  )
                                                )
                                              ),
                                              RegularGrammar::newEnd(45)
                                            )
                                          ),
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                            ),
                                            RegularGrammar::newEnd(46)
                                          )
                                        ),
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                            RegularGrammar::newCharacterClass(CharacterClass( Char('b')))
                                          ),
                                          RegularGrammar::newEnd(47)
                                        )
                                      ),
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('f')))
                                        ),
                                        RegularGrammar::newEnd(48)
                                      )
                                    ),
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                      ),
                                      RegularGrammar::newEnd(49)
                                    )
                                  ),
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                    ),
                                    RegularGrammar::newEnd(50)
                                  )
                                ),
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                  ),
                                  RegularGrammar::newEnd(51)
                                )
                              ),
                              RegularGrammar::newSequence(
                                RegularGrammar::newSequence(
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('v')))
                                ),
                                RegularGrammar::newEnd(52)
                              )
                            ),
                            RegularGrammar::newSequence(
                              RegularGrammar::newSequence(
                                RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
                              ),
                              RegularGrammar::newEnd(53)
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                              RegularGrammar::newCharacterClass(CharacterClass( Char('"')))
                            ),
                            RegularGrammar::newEnd(54)
                          )
                        ),
                        RegularGrammar::newSequence(
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                            RegularGrammar::newCharacterClass(CharacterClass( Char('?')))
                          ),
                          RegularGrammar::newEnd(55)
                        )
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newSequence(
                          RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                          RegularGrammar::newCharacterClass(CharacterClass( Char('\\')))
                        ),
                        RegularGrammar::newEnd(56)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newSequence(
                        RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                        RegularGrammar::newCharacterClass(CharacterClass( Char('/')))
                      ),
                      RegularGrammar::newEnd(57)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                      RegularGrammar::newCharacterClass(CharacterClass( Char(']')))
                    ),
                    RegularGrammar::newEnd(58)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                    RegularGrammar::newCharacterClass(CharacterClass( Char('-')))
                  ),
                  RegularGrammar::newEnd(59)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true))
                ),
                RegularGrammar::newEnd(60)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newCharacterClass(CharacterClass( Char(' '))),
              RegularGrammar::newEnd(61)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newCharacterClass(CharacterClass( Char('.'))),
            RegularGrammar::newEnd(62)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(63)
        )
      )
    )
  ),
  new LexicalContext("CCL", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSelection(
                            RegularGrammar::newSelection(
                              RegularGrammar::newSelection(
                                RegularGrammar::newSelection(
                                  RegularGrammar::newSelection(
                                    RegularGrammar::newSelection(
                                      RegularGrammar::newSelection(
                                        RegularGrammar::newSelection(
                                          RegularGrammar::newSelection(
                                            RegularGrammar::newSelection(
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newCharacterClass(CharacterClass( Char(']'))),
                                                RegularGrammar::newEnd(64)
                                              ),
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newCharacterClass(CharacterClass( Char('-'))),
                                                RegularGrammar::newEnd(65)
                                              )
                                            ),
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('^'))),
                                              RegularGrammar::newEnd(66)
                                            )
                                          ),
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('-'), Char('\\'), Char(']')}), true)),
                                            RegularGrammar::newEnd(67)
                                          )
                                        ),
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('X'), Char('x')})))
                                            ),
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')}))),
                                              RegularGrammar::newKleene(
                                                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')})))
                                              )
                                            )
                                          ),
                                          RegularGrammar::newEnd(68)
                                        )
                                      ),
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')}))),
                                            RegularGrammar::newKleene(
                                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')})))
                                            )
                                          )
                                        ),
                                        RegularGrammar::newEnd(69)
                                      )
                                    ),
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                        RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                      ),
                                      RegularGrammar::newEnd(70)
                                    )
                                  ),
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('b')))
                                    ),
                                    RegularGrammar::newEnd(71)
                                  )
                                ),
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('f')))
                                  ),
                                  RegularGrammar::newEnd(72)
                                )
                              ),
                              RegularGrammar::newSequence(
                                RegularGrammar::newSequence(
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                ),
                                RegularGrammar::newEnd(73)
                              )
                            ),
                            RegularGrammar::newSequence(
                              RegularGrammar::newSequence(
                                RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                              ),
                              RegularGrammar::newEnd(74)
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                              RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                            ),
                            RegularGrammar::newEnd(75)
                          )
                        ),
                        RegularGrammar::newSequence(
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                            RegularGrammar::newCharacterClass(CharacterClass( Char('v')))
                          ),
                          RegularGrammar::newEnd(76)
                        )
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newSequence(
                          RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                          RegularGrammar::newCharacterClass(CharacterClass( Char('\\')))
                        ),
                        RegularGrammar::newEnd(77)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newSequence(
                        RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                        RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
                      ),
                      RegularGrammar::newEnd(78)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                      RegularGrammar::newCharacterClass(CharacterClass( Char('"')))
                    ),
                    RegularGrammar::newEnd(79)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                    RegularGrammar::newCharacterClass(CharacterClass( Char('?')))
                  ),
                  RegularGrammar::newEnd(80)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                  RegularGrammar::newCharacterClass(CharacterClass( Char(']')))
                ),
                RegularGrammar::newEnd(81)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                RegularGrammar::newCharacterClass(CharacterClass( Char('-')))
              ),
              RegularGrammar::newEnd(82)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true))
            ),
            RegularGrammar::newEnd(83)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(84)
        )
      )
    )
  ),
  new LexicalContext("DOUBLE_QUOTED_STRING", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSelection(
                            RegularGrammar::newSelection(
                              RegularGrammar::newSelection(
                                RegularGrammar::newSelection(
                                  RegularGrammar::newSelection(
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                                      RegularGrammar::newEnd(85)
                                    ),
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('X'), Char('x')})))
                                        ),
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')}))),
                                          RegularGrammar::newKleene(
                                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')})))
                                          )
                                        )
                                      ),
                                      RegularGrammar::newEnd(86)
                                    )
                                  ),
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')}))),
                                        RegularGrammar::newKleene(
                                          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')})))
                                        )
                                      )
                                    ),
                                    RegularGrammar::newEnd(87)
                                  )
                                ),
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                  ),
                                  RegularGrammar::newEnd(88)
                                )
                              ),
                              RegularGrammar::newSequence(
                                RegularGrammar::newSequence(
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('b')))
                                ),
                                RegularGrammar::newEnd(89)
                              )
                            ),
                            RegularGrammar::newSequence(
                              RegularGrammar::newSequence(
                                RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                                RegularGrammar::newCharacterClass(CharacterClass( Char('f')))
                              ),
                              RegularGrammar::newEnd(90)
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                              RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                            ),
                            RegularGrammar::newEnd(91)
                          )
                        ),
                        RegularGrammar::newSequence(
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                            RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                          ),
                          RegularGrammar::newEnd(92)
                        )
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newSequence(
                          RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                          RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                        ),
                        RegularGrammar::newEnd(93)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newSequence(
                        RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                        RegularGrammar::newCharacterClass(CharacterClass( Char('v')))
                      ),
                      RegularGrammar::newEnd(94)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\')))
                    ),
                    RegularGrammar::newEnd(95)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                    RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
                  ),
                  RegularGrammar::newEnd(96)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('"')))
                ),
                RegularGrammar::newEnd(97)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                RegularGrammar::newCharacterClass(CharacterClass( Char('?')))
              ),
              RegularGrammar::newEnd(98)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true))
            ),
            RegularGrammar::newEnd(99)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(100)
        )
      )
    )
  ),
  new LexicalContext("LEX_STRING_LITERAL", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
          RegularGrammar::newEnd(101)
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(102)
        )
      )
    )
  ),
  new LexicalContext("ACTION", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('{'))),
                    RegularGrammar::newEnd(103)
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('}'))),
                    RegularGrammar::newEnd(104)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                  RegularGrammar::newEnd(105)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')}))),
                            RegularGrammar::newKleene(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')})))
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('X'), Char('x')}))),
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')}))),
                              RegularGrammar::newKleene(
                                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')})))
                              )
                            )
                          )
                        ),
                        RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true))
                      )
                    )
                  ),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
                ),
                RegularGrammar::newEnd(106)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true))
                ),
                RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
              ),
              RegularGrammar::newEnd(107)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(108)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(109)
        )
      )
    )
  ),
  new LexicalContext("CODE", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('{'))),
                    RegularGrammar::newEnd(110)
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('}'))),
                    RegularGrammar::newEnd(111)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                  RegularGrammar::newEnd(112)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')}))),
                            RegularGrammar::newKleene(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')})))
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('X'), Char('x')}))),
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')}))),
                              RegularGrammar::newKleene(
                                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')})))
                              )
                            )
                          )
                        ),
                        RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true))
                      )
                    )
                  ),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
                ),
                RegularGrammar::newEnd(113)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true))
                ),
                RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
              ),
              RegularGrammar::newEnd(114)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(115)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(116)
        )
      )
    )
  ),
  new LexicalContext("ACTION_DOUBLE_QUOTED_STRING", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSequence(
            RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
            RegularGrammar::newEnd(117)
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
            RegularGrammar::newEnd(118)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(119)
        )
      )
    )
  ),
  new LexicalContext("ACTION_DOUBLE_QUOTED_STRING_ESCAPE_SEQUENCE", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSelection(
                            RegularGrammar::newSelection(
                              RegularGrammar::newSelection(
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('X'), Char('x')}))),
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')}))),
                                      RegularGrammar::newKleene(
                                        RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')})))
                                      )
                                    )
                                  ),
                                  RegularGrammar::newEnd(120)
                                ),
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')}))),
                                    RegularGrammar::newKleene(
                                      RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')})))
                                    )
                                  ),
                                  RegularGrammar::newEnd(121)
                                )
                              ),
                              RegularGrammar::newSequence(
                                RegularGrammar::newCharacterClass(CharacterClass( Char('a'))),
                                RegularGrammar::newEnd(122)
                              )
                            ),
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Char('b'))),
                              RegularGrammar::newEnd(123)
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Char('f'))),
                            RegularGrammar::newEnd(124)
                          )
                        ),
                        RegularGrammar::newSequence(
                          RegularGrammar::newCharacterClass(CharacterClass( Char('n'))),
                          RegularGrammar::newEnd(125)
                        )
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newCharacterClass(CharacterClass( Char('r'))),
                        RegularGrammar::newEnd(126)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('t'))),
                      RegularGrammar::newEnd(127)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('v'))),
                    RegularGrammar::newEnd(128)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                  RegularGrammar::newEnd(129)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                RegularGrammar::newEnd(130)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
              RegularGrammar::newEnd(131)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newCharacterClass(CharacterClass( Char('?'))),
            RegularGrammar::newEnd(132)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(133)
        )
      )
    )
  ),
  new LexicalContext("STRING_LITERAL", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
          RegularGrammar::newEnd(134)
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(135)
        )
      )
    )
  ),
  new LexicalContext("COMMENT", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newCharacterClass(CharacterClass( Char('*'))),
              RegularGrammar::newCharacterClass(CharacterClass( Char('/')))
            ),
            RegularGrammar::newEnd(136)
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(137)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(138)
        )
      )
    )
  ),
  new LexicalContext("SINGLE_LINE_COMMENT", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSequence(
          RegularGrammar::newSequence(
            RegularGrammar::newOptional(
              RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
            ),
            RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
          ),
          RegularGrammar::newEnd(139)
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(140)
        )
      )
    )
  )},
  {
	{ 0, "{ return lgParser::KEYWORD_LEXER; }", 34},
	{ 1, "{\n\t\t\t\t\t\t\t\t\t\tcurrentValue.Identifier = lexicalGenerator->newIdentifier(std::string(begin(), end() - begin()));\n\t\t\t\t\t\t\t\t\t\treturn lgParser::IDENTIFIER;\n\t\t\t\t\t\t\t\t\t}", 35},
	{ 2, "{ push(Context::LEXER); return lgParser::OPERATOR_OPEN_CURLY_BRACE; }", 39},
	{ 3, "{ std::cerr << \"Extra invalid closing brace\" << std::endl; return ERROR; }", 40},
	{ 4, "{ push(Context::COMMENT); return IGNORE; }", 41},
	{ 5, "{ push(Context::SINGLE_LINE_COMMENT); return IGNORE; }", 42},
	{ 6, "{ return IGNORE; }", 43},
	{ 7, "{ newLine(); return IGNORE; }", 44},
	{ 8, "{\n    \t                                std::cerr << \"Invalid chararcter '\" << toString(*begin())\n    \t                                          << \"' in outer scope on line \" << getLineNumber() << std::endl;\n    \t                                return ERROR;\n    \t                            }", 45},
	{ 9, "{ return lgParser::KEYWORD_CONTEXT; }", 53},
	{ 10, "{ return lgParser::KEYWORD_START; }", 54},
	{ 11, "{ bracket_mode = MODE::CODE_BLOCK; return lgParser::KEYWORD_CODE; }", 55},
	{ 12, "{ bracket_mode = MODE::CODE_BLOCK; return lgParser::KEYWORD_HEADER; }", 56},
	{ 13, "{ return lgParser::KEYWORD_BASECLASS; }", 57},
	{ 14, "{ return lgParser::KEYWORD_ROOTTYPE; }", 58},
	{ 15, "{ return lgParser::KEYWORD_VALUETYPE; }", 59},
	{ 16, "{ return lgParser::KEYWORD_RETURNTYPE; }", 60},
	{ 17, "{\n\t\t\t\t\t\t\t\t\t\tcurrentValue.Identifier = lexicalGenerator->newIdentifier(std::string(begin(), end() - begin()));\n\t\t\t\t\t\t\t\t\t\treturn lgParser::IDENTIFIER;\n\t\t\t\t\t\t\t\t\t}", 62},
	{ 18, "{\n\t\t\t\t\t\t\t\t\t\tpush(Context::LEX_STRING_LITERAL);\n\t\t\t\t\t\t\t\t\t\tstringLiteral = \"\";\n\t\t\t\t\t\t\t\t\t\treturn IGNORE;\n\t\t\t\t\t\t\t\t\t}", 66},
	{ 19, "{\n\t\t\t\t\t\t\t\t\t  if (bracket_mode == MODE::NORMAL) {\n\t\t\t\t\t\t\t\t\t\tpush(Context::CONTEXT);\n\t\t\t\t\t\t\t\t\t    yyfnln = getLineNumber();\n\t\t\t\t\t\t\t\t\t\treturn lgParser::OPERATOR_OPEN_CURLY_BRACE;\n\t\t\t\t\t\t\t\t\t  }\n\t\t\t\t\t\t\t\t\t  else {\n\t\t\t\t\t\t\t\t\t\tpush(Context::CODE);\n\t\t\t\t\t\t\t\t\t\tcurley_braces = 1;\n\t\t\t\t\t\t\t\t\t\taction = \"\";\n\t\t\t\t\t\t\t\t\t\tbracket_mode = MODE::NORMAL;\n\t\t\t\t\t\t\t\t\t\tyyfnln = getLineNumber();\n\t\t\t\t\t\t\t\t\t\treturn IGNORE;\n\t\t\t\t\t\t\t\t\t  }\n\t\t\t\t\t\t\t\t\t}", 71},
	{ 20, "{ pop(); return lgParser::OPERATOR_CLOSE_CURLY_BRACE; }", 86},
	{ 21, "{ push(Context::COMMENT); return IGNORE; }", 87},
	{ 22, "{ push(Context::SINGLE_LINE_COMMENT); return IGNORE; }", 88},
	{ 23, "{ return IGNORE; }", 89},
	{ 24, "{ newLine(); return IGNORE; }", 90},
	{ 25, "{\n    \t                                std::cerr << \"Invalid character '\" << toString(*begin())\n    \t                                          << \"' in lexer block on line \" << getLineNumber() << std::endl;\n    \t                                return ERROR;\n    \t                            }", 91},
	{ 26, "{ push(Context::RE); return IGNORE; }", 99},
	{ 27, "{ push(Context::DOUBLE_QUOTED_STRING); return IGNORE; }", 100},
	{ 28, "{ push(Context::ACTION); yyfnln = getLineNumber(); curley_braces = 1; action = _begin[0]; return IGNORE; }", 101},
	{ 29, "{ pop(); return lgParser::OPERATOR_CLOSE_CURLY_BRACE; }", 102},
	{ 30, "{ push(Context::COMMENT); return IGNORE; }", 103},
	{ 31, "{ push(Context::SINGLE_LINE_COMMENT); return IGNORE; }", 104},
	{ 32, "{ return IGNORE; }", 105},
	{ 33, "{ newLine(); return IGNORE; }", 106},
	{ 34, "{\n    \t                                std::cerr << \"Invalid character '\" << toString(*begin())\n    \t                                          << \"' in context block on line \" << getLineNumber() << std::endl;\n    \t                                return ERROR;\n    \t                            }", 107},
	{ 35, "{ pop(); return IGNORE; }", 115},
	{ 36, "{ push(Context::CCL); currentValue.Symbol = *begin(); return lgParser::OPERATOR_OPEN_BRACE; }", 116},
	{ 37, "{ return lgParser::OPERATOR_OR; }", 117},
	{ 38, "{ return lgParser::OPERATOR_STAR; }", 118},
	{ 39, "{ return lgParser::OPERATOR_PLUS; }", 119},
	{ 40, "{ return lgParser::OPERATOR_QUERY; }", 120},
	{ 41, "{ return lgParser::OPERATOR_OPEN_PAREN; }", 121},
	{ 42, "{ return lgParser::OPERATOR_CLOSE_PAREN; }", 122},
	{ 43, "{ currentValue.Symbol = *begin(); return lgParser::SYMBOL; }", 123},
	{ 44, "{ currentValue.Symbol = (char) strtol(&_begin[2], &_end, 16); return lgParser::SYMBOL; }", 124},
	{ 45, "{ currentValue.Symbol = (char) strtol(&_begin[2], &_end, 8); return lgParser::SYMBOL; }", 125},
	{ 46, "{ currentValue.Symbol = '\\a'; return lgParser::SYMBOL; }", 126},
	{ 47, "{ currentValue.Symbol = '\\b'; return lgParser::SYMBOL; }", 127},
	{ 48, "{ currentValue.Symbol = '\\f'; return lgParser::SYMBOL; }", 128},
	{ 49, "{ currentValue.Symbol = '\\n'; return lgParser::SYMBOL; }", 129},
	{ 50, "{ currentValue.Symbol = '\\r'; return lgParser::SYMBOL; }", 130},
	{ 51, "{ currentValue.Symbol = '\\t'; return lgParser::SYMBOL; }", 131},
	{ 52, "{ currentValue.Symbol = '\\v'; return lgParser::SYMBOL; }", 132},
	{ 53, "{ currentValue.Symbol = '\\''; return lgParser::SYMBOL; }", 133},
	{ 54, "{ currentValue.Symbol = '\"'; return lgParser::SYMBOL; }", 134},
	{ 55, "{ currentValue.Symbol = '\\?'; return lgParser::SYMBOL; }", 135},
	{ 56, "{ currentValue.Symbol = '\\\\'; return lgParser::SYMBOL; }", 136},
	{ 57, "{ currentValue.Symbol = '/'; return lgParser::SYMBOL; }", 137},
	{ 58, "{ currentValue.Symbol = ']'; return lgParser::SYMBOL; }", 138},
	{ 59, "{ currentValue.Symbol = '-'; return lgParser::SYMBOL; }", 139},
	{ 60, "{\n    \t                                std::cerr << \"Invalid escape sequence '\\\\\" << _begin[1]\n    \t                                          << \"' in regular expression on line \" << getLineNumber() << std::endl;\n    \t                                return ERROR;\n    \t                            }", 140},
	{ 61, "{ currentValue.Symbol = ' '; return lgParser::SYMBOL; }", 145},
	{ 62, "{ return lgParser::OPERATOR_PERIOD; }", 146},
	{ 63, "{ currentValue.Symbol = *begin(); return lgParser::SYMBOL; }", 147},
	{ 64, "{ pop(); return lgParser::OPERATOR_CLOSE_BRACE; }", 151},
	{ 65, "{ return lgParser::OPERATOR_HYPHEN; }", 152},
	{ 66, "{ return lgParser::OPERATOR_CARET; }", 153},
	{ 67, "{ currentValue.Symbol = *begin(); return lgParser::SYMBOL; }", 154},
	{ 68, "{ currentValue.Symbol = (char) strtol(&_begin[2], &_end, 16); return lgParser::SYMBOL; }", 155},
	{ 69, "{ currentValue.Symbol = (char) strtol(&_begin[2], &_end, 8); return lgParser::SYMBOL; }", 156},
	{ 70, "{ currentValue.Symbol = '\\a'; return lgParser::SYMBOL; }", 157},
	{ 71, "{ currentValue.Symbol = '\\b'; return lgParser::SYMBOL; }", 158},
	{ 72, "{ currentValue.Symbol = '\\f'; return lgParser::SYMBOL; }", 159},
	{ 73, "{ currentValue.Symbol = '\\n'; return lgParser::SYMBOL; }", 160},
	{ 74, "{ currentValue.Symbol = '\\r'; return lgParser::SYMBOL; }", 161},
	{ 75, "{ currentValue.Symbol = '\\t'; return lgParser::SYMBOL; }", 162},
	{ 76, "{ currentValue.Symbol = '\\v'; return lgParser::SYMBOL; }", 163},
	{ 77, "{ currentValue.Symbol = '\\\\'; return lgParser::SYMBOL; }", 164},
	{ 78, "{ currentValue.Symbol = '\\''; return lgParser::SYMBOL; }", 165},
	{ 79, "{ currentValue.Symbol = '\"'; return lgParser::SYMBOL; }", 166},
	{ 80, "{ currentValue.Symbol = '\\?'; return lgParser::SYMBOL; }", 167},
	{ 81, "{ currentValue.Symbol = ']'; return lgParser::SYMBOL; }", 168},
	{ 82, "{ currentValue.Symbol = '-'; return lgParser::SYMBOL; }", 169},
	{ 83, "{\n    \t                                std::cerr << \"Invalid escape sequence '\\\\\" << *begin()\n    \t                                          << \"' in character class on line \" << getLineNumber() << std::endl;\n    \t                                return ERROR;\n    \t                            }", 170},
	{ 84, "{\n    \t                                std::cerr << \"Invalid chararcter '\" << *begin()\n    \t                                          << \"' in character class on line \" << getLineNumber() << std::endl;\n    \t                                return ERROR;\n    \t                            }", 175},
	{ 85, "{ pop(); return IGNORE; }", 183},
	{ 86, "{ currentValue.Symbol = (char) strtol(&_begin[2], &_end, 16); return lgParser::SYMBOL; }", 184},
	{ 87, "{ currentValue.Symbol = (char) strtol(&_begin[2], &_end, 8); return lgParser::SYMBOL; }", 185},
	{ 88, "{ currentValue.Symbol = '\\a'; return lgParser::SYMBOL; }", 186},
	{ 89, "{ currentValue.Symbol = '\\b'; return lgParser::SYMBOL; }", 187},
	{ 90, "{ currentValue.Symbol = '\\f'; return lgParser::SYMBOL; }", 188},
	{ 91, "{ currentValue.Symbol = '\\n'; return lgParser::SYMBOL; }", 189},
	{ 92, "{ currentValue.Symbol = '\\r'; return lgParser::SYMBOL; }", 190},
	{ 93, "{ currentValue.Symbol = '\\t'; return lgParser::SYMBOL; }", 191},
	{ 94, "{ currentValue.Symbol = '\\v'; return lgParser::SYMBOL; }", 192},
	{ 95, "{ currentValue.Symbol = '\\\\'; return lgParser::SYMBOL; }", 193},
	{ 96, "{ currentValue.Symbol = '\\''; return lgParser::SYMBOL; }", 194},
	{ 97, "{ currentValue.Symbol = '\"'; return lgParser::SYMBOL; }", 195},
	{ 98, "{ currentValue.Symbol = '?'; return lgParser::SYMBOL; }", 196},
	{ 99, "{\n    \t                                std::cerr << \"Invalid escape sequence '\\\\\" << _begin[1]\n    \t                                          << \"' in quoted string on line \" << getLineNumber() << std::endl;\n    \t                                return ERROR;\n    \t                            }", 197},
	{ 100, "{ currentValue.Symbol = *begin(); return lgParser::SYMBOL; }", 202},
	{ 101, "{\n\t\t\t\t\t\t\t\t\t\tcurrentValue.StringLiteral = stringLiteral.c_str();\n\t\t\t\t\t\t\t\t\t\tpop();\n\t\t\t\t\t\t\t\t\t\treturn lgParser::STRING_LITERAL;\n\t\t\t\t\t\t\t\t\t}", 206},
	{ 102, "{\n\t\t\t\t\t\t\t\t\t\tstringLiteral += *begin();\n\t\t\t\t\t\t\t\t\t\treturn IGNORE;\n\t\t\t\t\t\t\t\t\t}", 211},
	{ 103, "{ action += *begin(); ++curley_braces; return IGNORE; }", 218},
	{ 104, "{\n                    \t\t\t\t\t\t\t\t\taction += \"}\";\n                    \t\t\t\t\t\t\t\t\tif (--curley_braces == 0) {\n                    \t\t\t\t\t\t\t\t\t\tpop();\n                    \t\t\t\t\t\t\t\t\t\tcurrentValue.Action = action.c_str();\n                    \t\t\t\t\t\t\t\t\t\treturn lgParser::TOKEN_ACTION;\n                    \t\t\t\t\t\t\t\t\t}\n                    \t\t\t\t\t\t\t\t\treturn IGNORE;\n                    \t\t\t\t\t\t\t\t}", 219},
	{ 105, "{ push(ACTION_DOUBLE_QUOTED_STRING); action += \"\\\"\"; return IGNORE; }", 228},
	{ 106, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 229},
	{ 107, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 234},
	{ 108, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  newLine();\n\t\t\t\t\t\t\t\t\t\t\t\t\t  action += '\\n';\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 239},
	{ 109, "{ action += *begin(); return IGNORE; }", 244},
	{ 110, "{ action += *begin(); ++curley_braces; return IGNORE; }", 248},
	{ 111, "{\n                    \t\t\t\t\t\t\t\t\tif (--curley_braces == 0) {\n                    \t\t\t\t\t\t\t\t\t\tpop();\n                    \t\t\t\t\t\t\t\t\t\tcurrentValue.CodeBlock = new CodeBlock(action, yyfnln, filename);\n                    \t\t\t\t\t\t\t\t\t\treturn lgParser::TOKEN_CODE;\n                    \t\t\t\t\t\t\t\t\t}\n\t\t\t\t\t\t\t\t\t\t\t\t\t\telse {\n\t                    \t\t\t\t\t\t\t\t\taction += \"}\";\n\t\t                \t\t\t\t\t\t\t\t\treturn IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n                    \t\t\t\t\t\t\t\t}", 249},
	{ 112, "{ push(ACTION_DOUBLE_QUOTED_STRING); action += \"\\\"\"; return IGNORE; }", 260},
	{ 113, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 261},
	{ 114, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 266},
	{ 115, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  newLine();\n\t\t\t\t\t\t\t\t\t\t\t\t\t  action += '\\n';\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 271},
	{ 116, "{ action += *begin(); return IGNORE; }", 276},
	{ 117, "{ action += *begin(); pop(); return IGNORE; }", 280},
	{ 118, "{ action += *begin(); push(ACTION_DOUBLE_QUOTED_STRING_ESCAPE_SEQUENCE); return IGNORE; }", 281},
	{ 119, "{ action += *begin(); return IGNORE; }", 282},
	{ 120, "{\n\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t  pop();\n\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t}", 286},
	{ 121, "{\n\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t  pop();\n\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t}", 292},
	{ 122, "{ action += *begin(); pop(); return IGNORE; }", 298},
	{ 123, "{ action += *begin(); pop(); return IGNORE; }", 299},
	{ 124, "{ action += *begin(); pop(); return IGNORE; }", 300},
	{ 125, "{ action += *begin(); pop(); return IGNORE; }", 301},
	{ 126, "{ action += *begin(); pop(); return IGNORE; }", 302},
	{ 127, "{ action += *begin(); pop(); return IGNORE; }", 303},
	{ 128, "{ action += *begin(); pop(); return IGNORE; }", 304},
	{ 129, "{ action += *begin(); pop(); return IGNORE; }", 305},
	{ 130, "{ action += *begin(); pop(); return IGNORE; }", 306},
	{ 131, "{ action += *begin(); pop(); return IGNORE; }", 307},
	{ 132, "{ action += *begin(); pop(); return IGNORE; }", 308},
	{ 133, "{\n    \t                                std::cerr << \"Invalid escape sequence '\\\\\" << *begin()\n    \t                                          << \"' in quoted string on line \" << getLineNumber() << std::endl;\n\t\t\t\t\t\t\t\t\t\taction += *begin();\n\t\t\t\t\t\t\t\t\t\tpop();\n    \t                                return ERROR;\n    \t                            }", 309},
	{ 134, "{\n\t\t\t\t\t\t\t\t\t\tcurrentValue.StringLiteral = stringLiteral.c_str();\n\t\t\t\t\t\t\t\t\t\tpop();\n\t\t\t\t\t\t\t\t\t\treturn lgParser::STRING_LITERAL;\n\t\t\t\t\t\t\t\t\t}", 318},
	{ 135, "{\n\t\t\t\t\t\t\t\t\t\tstringLiteral += *begin();\n\t\t\t\t\t\t\t\t\t\treturn IGNORE;\n\t\t\t\t\t\t\t\t\t}", 323},
	{ 136, "{ pop(); return IGNORE; }", 329},
	{ 137, "{ newLine(); return IGNORE; }", 330},
	{ 138, "{ return IGNORE;}", 331},
	{ 139, "{ newLine(); pop(); return IGNORE; }", 334},
	{ 140, "{ return IGNORE; }", 335}
  }),
  "RegularGrammar",
  "Lexer",
  "ValueType",
  "int",
  {
    { "\n\t\t#include <string>\n\t\t#include \"lg.pg.h\"\n\t\t#include \"nonstd/Utils.h\"\n\n\t\tenum MODE { NORMAL, CODE_BLOCK };\n\t", 9, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\lg-bootstrap-lg\\lg.lg" }
  },
  {
    { "\n\t\tstd::string action;\n\t\tchar identifier[132];\n\t\tstd::string stringLiteral;\n\t\tint yyfnln;\n\t\tint curley_braces = 0;\n\t\tMODE bracket_mode = NORMAL;\n\n\t\textern LexicalGenerator*\tlexicalGenerator;\n\n\t\tusing namespace Runtime;\n\t", 16, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\lg-bootstrap-lg\\lg.lg" }
  }
);

// End C:\Users\aaron\Projects\G\latest\G - saving 6\src\bootstrap\self-bootstrap\lg-bootstrap-lg\lg.lexer.cpp
