# Reusing twig templates

All three of these twig "tags" let you reuse templates:
* `include` lets you pass variables, but you can't override "blocks".
* `extends` lets you override "blocks", but not pass variables -- AND, when you use `extends`, you are completely taking over the template you're working on -- you can't put stuff before the `extends` tag, and you can't do anything that isn't between `block`/`endblock` (block override) tags.
* With `embed`, you get everything from `include` and `extends`.
  * I still usually use `include` unless I need to override blocks.  If you aren't overriding blocks, it's like, why bother with an embed, it's just extra code.


## More details

Look at the twig docs! -- but...

### Include ([twig docs](https://twig.symfony.com/doc/2.x/tags/include.html))
A simple use of "include" is to literally and simply insert an entire template in a particular spot.  "La la la la RIGHT HERE la la la la" -- RIGHT HERE we insert a totally different template file, as-is.
A more complex use of "include" (you'll see this all over your Palantir templates), is `include ... with`
* "include with" allows you to pass variables from the includING template to the includED template.

### Extends ([twig docs](https://twig.symfony.com/doc/2.x/tags/extends.html))
`extends` _**also**_ lets you reuse another template.  You can't pass variables, but you can override "blocks".
* WARNING: If you use `extends`, you can't do anything that isn't inside a `block` tag.
* **_In my opinion/experience,_** the reason to use `extends` is if you want to reuse another template, but override one or more sections.
  * I don't use `extends` basically ever these days, I prefer to use `include` or `embed` so I can pass variables.
  * (Again, you can't pass variables with "extends")

### Embed ([twig docs](https://twig.symfony.com/doc/2.x/tags/embed.html))

So, `embed` puts it all together.

With embed:
* You can pass variables (same syntax as passing variables with "include": `embed ... with`)
* You can override "blocks"

And:
* Embed requires opening and closing tags (`embed`/`endembed`)
* You can do things before/after an embed (unlike how "extends" is a total takeover of your template).

-------

### Block
By the way, what is "block"?

"block" tag, in the official [twig docs](https://twig.symfony.com/doc/2.x/tags/block.html) (and the related [block function](https://twig.symfony.com/doc/2.x/functions/block.html)):
> Blocks are used for inheritance and act as placeholders and replacements at the same time. They are documented in detail in the documentation for the [extends](https://twig.symfony.com/doc/2.x/tags/extends.html) tag.
> Block names must consist of alphanumeric characters, and underscores. The first char can't be a digit and dashes are not permitted.

Put another way:
You can define replaceable content with Twig "blocks": "Twig blocks are essentially swappable pieces of a template file" ([source](https://atendesigngroup.com/articles/template-inheritance-drupal-8-twig-extend)).

----

## Examples of include/embed

Take this views template, from an imaginary base theme:<br>
[@example_base/views-view.html.twig](https://github.com/alisonjo315/alison-randomness/blob/main/twig/example_base/templates/views-view.html.twig)

Two "re-uses" of that template, in our "demo" child theme:

* Example with `include` -- here, all that's happening is we're passing variables to customize the classes:<br>
  [@example_child/views-view--news--block-teaser.html.twig](https://github.com/alisonjo315/alison-randomness/blob/main/twig/example_child/templates/views-view--news--block-teaser.html.twig)
* Example with `embed` -- here, we're passing variables to customize the classes, AND overriding one "block":<br>
  [@example_child/views-view--news.html.twig](https://github.com/alisonjo315/alison-randomness/blob/main/twig/example_child/templates/views-view--news.html.twig)
