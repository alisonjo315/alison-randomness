Special thank you to my colleague, Eric Woods, for the code samples and notes!

Generic example of a Drush command to edit nodes.  It also needs a `drush.services.yml` file in the top directory of the module defines the commands.

Oh, and then you cache-rebuild and run something like `drush my_module:example-action --dry-run` or `drush example`. You don't need to cache-rebuild once your example is registered as a command, you can edit and re-run.

If we were extra clever, we could make something like this into a `drush generate` function and THAT is what we use to build new commands like you were thinking about [other colleague]. I put pieces into this example that always seem to catch me on commands:

* What's the syntax for specifying parameters / options
* Remember to use `accessCheck(FALSE)`
* How to deal with loading too much data
* How to access fields
* Pretty printing output

----

Alison here 👋  One another link that may or may not help:
* https://www.fourkitchens.com/blog/development/custom-drush-commands-drush-generate/

⚠️ And, general reminder: Good idea to create a fresh site backup before running anything like this on a production site!
